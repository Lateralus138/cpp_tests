#include "pch.h"
#include "ArgumentParser.h"
#include <fstream>

namespace fs = std::filesystem;

// Base64 encode function
std::string base64_encode(const std::vector<unsigned char>& data) {
    static const char* base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string encoded;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    for (auto c : data) {
        char_array_3[i++] = c;
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for(i = 0; i < 4; i++) encoded += base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    if (i) {
        for(j = i; j < 3; j++) char_array_3[j] = '\0';
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        for (j = 0; j < i + 1; j++) encoded += base64_chars[char_array_4[j]];
        while((i++ < 3)) encoded += '=';
    }
    return encoded;
}

// Cairo read function for stdin
cairo_status_t read_from_stdin(void *closure, unsigned char *data, unsigned int length) {
    size_t read = fread(data, 1, length, stdin);
    return read == length ? CAIRO_STATUS_SUCCESS : CAIRO_STATUS_READ_ERROR;
}

// Helper functions to reduce main complexity

cairo_surface_t* load_image(const std::optional<std::string>& input_file) {
    cairo_surface_t* surface = nullptr;
    try {
        if (input_file) {
            // Use C GdkPixbuf API to avoid GTKMM wrapping issues
            GError *error = nullptr;
            GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(input_file->c_str(), &error);
            if (!pixbuf) {
                std::cerr << "Error loading image: " << (error ? error->message : "unknown") << std::endl;
                if (error) g_error_free(error);
                return nullptr;
            }
            int width = gdk_pixbuf_get_width(pixbuf);
            int height = gdk_pixbuf_get_height(pixbuf);
            // Create ARGB32 Cairo surface
            surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
            cairo_t* cr = cairo_create(surface);
            // Draw pixbuf onto surface
            gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
            cairo_paint(cr);
            cairo_destroy(cr);
            g_object_unref(pixbuf);
        } else {
            // For stdin, assume PNG format
            surface = cairo_image_surface_create_from_png_stream(read_from_stdin, NULL);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading image: " << e.what() << std::endl;
        if (surface) cairo_surface_destroy(surface);
        return nullptr;
    }
    if (!surface || cairo_surface_status(surface) != CAIRO_STATUS_SUCCESS) {
        std::cerr << "Error creating surface: " << (surface ? cairo_status_to_string(cairo_surface_status(surface)) : "null surface") << std::endl;
        if (surface) cairo_surface_destroy(surface);
        return nullptr;
    }
    return surface;
}

std::string determine_icon_name(const std::optional<std::string>& input_file) {
    std::string icon_name = "icon";
    if (input_file) {
        fs::path p = *input_file;
        icon_name = p.stem().string();
    }
    return icon_name;
}

std::string determine_output_base(const std::optional<std::string>& custom_path, bool system_install) {
    std::string output_base;
    if (custom_path) {
        output_base = *custom_path;
        std::cout << "Using custom output path: " << output_base << std::endl;
    } else if (system_install) {
        output_base = "/usr/share/icons/hicolor";
        std::cout << "Installing to system icon directory: " << output_base << std::endl;
    } else {
        const char* home = getenv("HOME");
        if (!home) {
            std::cerr << "HOME environment variable not set" << std::endl;
            return "";
        }
        output_base = std::string(home) + "/.local/share/icons/hicolor";
        std::cout << "Installing to user icon directory: " << output_base << std::endl;
    }
    return output_base;
}

void generate_pngs(cairo_surface_t* surface, const std::string& temp_base, const std::string& icon_name) {
    std::vector<int> sizes = {16, 22, 24, 32, 48, 64, 128, 256};
    int width = cairo_image_surface_get_width(surface);
    int height = cairo_image_surface_get_height(surface);

    for (int size : sizes) {
        std::string dir = temp_base + "/" + std::to_string(size) + "x" + std::to_string(size) + "/apps/";
        fs::create_directories(dir);
        cairo_surface_t* scaled = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, size, size);
        cairo_t* cr = cairo_create(scaled);
        cairo_scale(cr, (double)size / width, (double)size / height);
        cairo_set_source_surface(cr, surface, 0, 0);
        cairo_paint(cr);
        std::string filename = dir + icon_name + ".png";
        cairo_status_t status = cairo_surface_write_to_png(scaled, filename.c_str());
        if (status != CAIRO_STATUS_SUCCESS) {
            std::cerr << "Error saving PNG: " << cairo_status_to_string(status) << std::endl;
            exit(1);
        }
        cairo_destroy(cr);
        cairo_surface_destroy(scaled);
    }
}

bool create_svg(cairo_surface_t* surface, const std::string& temp_base, const std::string& icon_name) {
    std::string svg_dir = temp_base + "/scalable/apps/";
    fs::create_directories(svg_dir);
    std::string svg_file = svg_dir + icon_name + ".svg";
    try {
        std::string temp_png = temp_base + "/temp.png";
        cairo_surface_write_to_png(surface, temp_png.c_str());
        std::ifstream file(temp_png, std::ios::binary);
        std::vector<unsigned char> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        std::string b64 = base64_encode(data);
        int width = cairo_image_surface_get_width(surface);
        int height = cairo_image_surface_get_height(surface);
        std::string svg_content = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                  "<svg width=\"" + std::to_string(width) + "\" "
                                  "height=\"" + std::to_string(height) + "\" "
                                  "xmlns=\"http://www.w3.org/2000/svg\" "
                                  "xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
                                  "<image width=\"" + std::to_string(width) + "\" "
                                  "height=\"" + std::to_string(height) + "\" "
                                  "xlink:href=\"data:image/png;base64," + b64 + "\"/>\n"
                                  "</svg>\n";
        std::ofstream svg_out(svg_file);
        svg_out << svg_content;
        svg_out.close();
        fs::remove(temp_png);
    } catch (const std::exception& e) {
        std::cerr << "Error creating SVG: " << e.what() << std::endl;
        return false;
    }
    return true;
}

// Remove dangling symlinks recursively
void remove_dangling_symlinks(const fs::path& dir) {
    if (!fs::exists(dir) || !fs::is_directory(dir)) return;
    for (const auto& entry : fs::recursive_directory_iterator(dir)) {
        if (fs::is_symlink(entry)) {
            try {
                auto target = fs::read_symlink(entry);
                if (!fs::exists(target)) {
                    fs::remove(entry);
                }
            } catch (...) {
                // Ignore errors
            }
        }
    }
}

bool install_icons(const std::string& temp_base, const std::string& output_base, const std::string& icon_name) {
    try {
        fs::create_directories(output_base);
        remove_dangling_symlinks(output_base);
        std::vector<int> sizes = {16, 22, 24, 32, 48, 64, 128, 256};
        for (int size : sizes) {
            std::string src_file = temp_base + "/" + std::to_string(size) + "x" + std::to_string(size) + "/apps/" + icon_name + ".png";
            std::string dest_dir = output_base + "/" + std::to_string(size) + "x" + std::to_string(size) + "/apps";
            fs::create_directories(dest_dir);
            std::string dest_file = dest_dir + "/" + icon_name + ".png";
            if (fs::exists(dest_file)) {
                fs::remove(dest_file);
            }
            fs::copy_file(src_file, dest_file, fs::copy_options::overwrite_existing);
        }
        std::string src_svg = temp_base + "/scalable/apps/" + icon_name + ".svg";
        std::string dest_scalable_dir = output_base + "/scalable/apps";
        fs::create_directories(dest_scalable_dir);
        std::string dest_svg = dest_scalable_dir + "/" + icon_name + ".svg";
        if (fs::exists(dest_svg)) {
            fs::remove(dest_svg);
        }
        fs::copy_file(src_svg, dest_svg, fs::copy_options::overwrite_existing);
        std::cout << "Copy successful" << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error copying to output: " << e.what() << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    using namespace argparser;

    Glib::init();
    gtk_init(&argc, &argv);
    ArgumentParser parser(argc, argv);
    parser.add_switch_pair("h", "help", "  This help message.", SwitchType::FLAG, Requirement::OPTIONAL);
    parser.add_switch_pair("i", "input", "  Image file (PNG, JPG, BMP, ICO, etc.) or stdin (PNG only).", SwitchType::PARAMETER, Requirement::OPTIONAL);
    parser.add_switch_pair("n", "name", "  Custom name for the output icon (without extension).", SwitchType::PARAMETER, Requirement::OPTIONAL);
    parser.add_switch_pair("s", "system", "  Output is for the system. /usr/share/icons/hicolor.\n    Output defaults to user; ~/.local/share/icons/hicolor.\n    When installing for system root (sudo) privileges must\n    be granted.", SwitchType::FLAG, Requirement::OPTIONAL);
    parser.add_switch_pair("p", "path", "  Custom output; overrides user and system. Great for\n    if we need to package for an application.", SwitchType::PARAMETER, Requirement::OPTIONAL);

    try {
        parser.parse();
    } catch (const ArgumentParserException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    if (parser.is_switch_set("help")) {
        parser.print_help("img2hicolor: Convert image to hicolor icon theme.");
        std::cout << '\n';
        return 0;
    }

    // Get options
    std::optional<std::string> input_file = parser.get_switch_value("input");
    std::optional<std::string> custom_path = parser.get_switch_value("path");
    std::optional<std::string> custom_name = parser.get_switch_value("name");
    bool system_install = parser.is_switch_set("system");

    // Load image
    cairo_surface_t* surface = load_image(input_file);
    if (!surface) {
        return 1;
    }

    // Determine icon name
    std::string icon_name;
    if (custom_name) {
        icon_name = *custom_name;
    } else {
        icon_name = determine_icon_name(input_file);
    }

    // Determine output base
    std::string output_base = determine_output_base(custom_path, system_install);
    if (output_base.empty()) {
        cairo_surface_destroy(surface);
        return 1;
    }

    // Create temp directory
    std::string temp_base = "/tmp/img2hicolor_" + std::to_string(getpid()) + "_" + std::to_string(time(nullptr));
    fs::create_directories(temp_base);

    // Generate PNGs
    generate_pngs(surface, temp_base, icon_name);

    // Create SVG
    if (!create_svg(surface, temp_base, icon_name)) {
        cairo_surface_destroy(surface);
        fs::remove_all(temp_base);
        return 1;
    }

    // Install icons
    if (!install_icons(temp_base, output_base, icon_name)) {
        cairo_surface_destroy(surface);
        fs::remove_all(temp_base);
        return 1;
    }

    // Clean up
    cairo_surface_destroy(surface);
    fs::remove_all(temp_base);

    return 0;
}
