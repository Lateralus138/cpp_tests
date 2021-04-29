#include <gtkmm.h>
using namespace std;
using namespace Gtk;
 
class GTKTest : public Window
{
    // controls
 
    protected: 
        VBox vBoxMain;
        Label labelTextToDisplay;
        Entry entryTextToDisplay;
        Label labelDisplayTo;
        ComboBoxText comboBoxDisplayTo;
        CheckButton checkButtonPrependMessage;
        Button buttonDisplay;
 
    // methods
 
    public: GTKTest()
    {
        set_border_width(10);
        // set_text("YO");
        // add_label("HEY");
 
        // vBoxMain
        add(vBoxMain);
        vBoxMain.show();
 
        // labelTextToDisplay
        labelTextToDisplay.set_label("Text to Display:");
        vBoxMain.add(labelTextToDisplay);
        labelTextToDisplay.show();
 
        // entryTextToDisplay
        entryTextToDisplay.set_text("This is a test!");
        vBoxMain.add(entryTextToDisplay);
        entryTextToDisplay.show();
 
        // labelDisplayTo
        labelDisplayTo.set_label("Display to:");
        vBoxMain.add(labelDisplayTo);
        labelDisplayTo.show();
 
        // comboBoxDisplayTo
        comboBoxDisplayTo.append("Console");
        comboBoxDisplayTo.append("Dialog");
        comboBoxDisplayTo.set_active(0);
        vBoxMain.add(comboBoxDisplayTo);
        comboBoxDisplayTo.show();
 
        // checkButtonPrependMessage
        checkButtonPrependMessage.set_label("Prepend 'Message: '");
        vBoxMain.add(checkButtonPrependMessage);
        checkButtonPrependMessage.show();
 
        // buttonDisplay
        buttonDisplay.set_label("Display");
        buttonDisplay.signal_clicked().connect
        (
            sigc::mem_fun
            (
                *this,
                &GTKTest::buttonDisplayClicked
            )
        );
        vBoxMain.add(buttonDisplay);
        buttonDisplay.show();
    }
 
    // event handlers
 
    protected: void buttonDisplayClicked()
    {
        string textToDisplay = entryTextToDisplay.get_text();
 
        bool prependMessage = checkButtonPrependMessage.get_active();
        if (prependMessage == true)
        {
            textToDisplay.insert(0, "Message: ");
        }
 
        string displayMode = comboBoxDisplayTo.get_active_text();
 
        if (displayMode == "Console")
        {
            printf("%s\n", textToDisplay.c_str());
        }
        else if (displayMode == "Dialog")
        {       
            MessageDialog dialog(textToDisplay);
            dialog.run();
        }
        else
        {
            throw runtime_error("Unrecognized display mode!");
        }
    }
};
 
int main (int argc, char *argv[])
{
    Main kit(argc, argv);
    GTKTest GTKTest;
    Main::run(GTKTest);
    return 0;
}