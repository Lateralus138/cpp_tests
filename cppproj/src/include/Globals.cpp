#include "Globals.h"
Globals globals;
void Globals::pch_content_create(Parameters &params)
{
  pch_content =
    "#ifndef PCH_H"
    "\n#define PCH_H"
    "\n#include <iostream>";
  for (const std::string class_name : params.class_names)
  {
    if (class_name == "pch") continue;
    pch_content.append("\n#include \"");
    pch_content.append(class_name);
    pch_content.append(".h\"");
  }
  pch_content.append("\n#endif \\\\ PCH_H\n");
}
void Globals::makefile_content_create(Parameters &params)
{
  makefile_content =
    "SHELL = bash"
    "\nPROJNM = "
    "\nAND32GXX = arm-linux-gnueabihf-g++"
    "\nAND64GXX = aarch64-linux-gnu-g++"
    "\n"
    "\nSRCDIR = src"
    "\nINCDIR = $(SRCDIR)/include"
    "\nLIBDIR = $(SRCDIR)/lib"
    "\nDBGDIR = debug"
    "\nDBGDYNDIR = $(DBGDIR)/dynamic"
    "\nDBGSTCDIR = $(DBGDIR)/static"
    "\nRELDIR = release"
    "\nRELDYNDIR = $(RELDIR)/dynamic"
    "\nRELSTCDIR = $(RELDIR)/static"
    "\nTSTDIR = test"
    "\nTSTDYNDIR = $(TSTDIR)/dynamic"
    "\nTSTSTCDIR = $(TSTDIR)/static"
    "\nANDDIR = android"
    "\nANDDYNDIR = $(ANDDIR)/dynamic"
    "\nANDDYNDIR32 = $(ANDDYNDIR)/32"
    "\nANDDYNDIR64 = $(ANDDYNDIR)/64"
    "\nANDSTCDIR = $(ANDDIR)/static"
    "\nANDSTCDIR32 = $(ANDSTCDIR)/32"
    "\nANDSTCDIR64 = $(ANDSTCDIR)/64"
    "\n"
    "\nMAINNM = ";
  makefile_content.append(params.main_name);
  makefile_content.append
  (
    "\nMAINEX = cpp"
    "\nMAINFL = $(MAINNM).$(MAINEX)"
    "\n"
    "\nSRCFLS = $(wildcard $(SRCDIR)/*.cpp)"
    "\nOBJSRC = $(wildcard $(INCDIR)/*.cpp)"
    "\nOBJOBJ = $(subst include,lib,$(patsubst %.cpp,%.o,$(OBJSRC)))"
    "\nDBGDYN = $(DBGDYNDIR)/$(PROJNM)"
    "\nDBGSTC = $(DBGSTCDIR)/$(PROJNM)"
    "\nTGTDYN = $(RELDYNDIR)/$(PROJNM)"
    "\nTGTSTC = $(RELSTCDIR)/$(PROJNM)"
    "\nTSTDYN = $(TSTDYNDIR)/$(PROJNM)"
    "\nTSTSTC = $(TSTSTCDIR)/$(PROJNM)"
    "\nANDDYN32 = $(ANDDYNDIR32)/$(PROJNM)"
    "\nANDDYN64 = $(ANDDYNDIR64)/$(PROJNM)"
    "\nANDSTC32 = $(ANDSTCDIR32)/$(PROJNM)"
    "\nANDSTC64 = $(ANDSTCDIR64)/$(PROJNM)"
    "\n"
    "\nTSTEXE = $(TSTDYN) # or $(TSTSTC)"
    "\nTSTARG = # --help # $(TSTEXE)"
    "\n"
    "\n# GTKINC = $(shell pkg-config gtkmm-3.0 --cflags)"
    "\n# GTKLIB = $(shell pkg-config gtkmm-3.0 --libs)"
    "\n"
    "\nLDFLAG = -I$(INCDIR) -O3 -std=c++20"
    "\nANDFLG = $(LDFLAG) -march=armv8.5-a"
    "\nLDLIBS = -L$(LIBDIR) -l$(PROJNM)"
    "\n"
    "\nDBGFLG = -ggdb -Wall -Wextra -std=c++20"
    "\n"
    "\nSNFLGS = 	-fsanitize=undefined \\"
    "\n			   	-fno-sanitize-recover=all -fsanitize=float-divide-by-zero \\"
    "\n				 	-fsanitize=float-cast-overflow -fno-sanitize=null \\"
    "\n				 	-fno-sanitize=alignment -std=c++20"
    "\n"
    "\nSNFLGD = $(SNFLGS) -fsanitize=address"
    "\n"
    "\n#STFLAG = -static -static-libgcc -static-libstdc++"
    "\nSTFLAG = -static"
    "\n"
    "\nPCHFIL = $(INCDIR)/pch.h"
    "\n"
    "\nall: releasedynamicall"
    "\n"
    "\npch:"
    "\n	@echo Precompile headers"
    "\n	$(CXX) $(PCHFIL)"
    "\n"
    "\nreleasedynamic: builddirectories"
    "\n	@echo Building dynamic executable"
    "\n	$(CXX) $(GTKINC) $(LDFLAG) $(SRCFLS) -o $(TGTDYN) $(LDLIBS) $(GTKLIB)"
    "\n	strip $(TGTDYN)"
    "\n"
    "\nreleasedynamicall: cleanreleasedynamic builddirectories pch buildlibslinux"
    "\n	@echo Building dynamic executable"
    "\n	$(CXX) $(GTKINC) $(LDFLAG) $(SRCFLS) -o $(TGTDYN) $(LDLIBS) $(GTKLIB)"
    "\n	strip $(TGTDYN)"
    "\n"
    "\nreleasestaticall: cleanreleasestatic builddirectories pch buildlibslinux"
    "\n	@echo Building static executable"
    "\n	$(CXX) $(GTKINC) $(STFLAG) $(LDFLAG) $(SRCFLS) -o $(TGTSTC) $(LDLIBS) $(GTKLIB)"
    "\n	strip $(TGTSTC)"
    "\n"
    "\nreleasestatic: builddirectories"
    "\n	@echo Building static executable"
    "\n	$(CXX) $(GTKINC) $(STFLAG) $(LDFLAG) $(SRCFLS) -o $(TGTSTC) $(LDLIBS) $(GTKLIB)"
    "\n	strip $(TGTSTC)"
    "\n"
    "\nandroidall: androidstaticall androiddynamicall"
    "\n"
    "\nandroidstaticall:	android32staticall android64staticall"
    "\n"
    "\nandroid32staticall: cleanandroid32static builddirectories pch buildallobjectsandroidarm32 buildarchivelinux"
    "\n	@echo Building static Android 32 bit executable"
    "\n	$(AND32GXX) -static $(ANDFLG) $(SRCFLS) -o $(ANDSTC32).arm32 $(LDLIBS)"
    "\n"
    "\nandroid32static: cleanandroid32static builddirectories"
    "\n	@echo Building static Android 32 bit executable"
    "\n	$(AND32GXX) -static $(ANDFLG) $(SRCFLS) -o $(ANDSTC32) $(LDLIBS)"
    "\n"
    "\nandroid64staticall: cleanandroid64static builddirectories pch buildallobjectsandroidaarch64 buildarchivelinux"
    "\n	@echo Building static Android 64 bit executable"
    "\n	$(AND64GXX) $(STFLAG) $(ANDFLG) $(SRCFLS) -o $(ANDSTC64).aarch64 $(LDLIBS)"
    "\n"
    "\nandroid64static: cleanandroid64static builddirectories"
    "\n	@echo Building static Android 64 bit executable"
    "\n	$(AND64GXX) -static $(ANDFLG) $(SRCFLS) -o $(ANDSTC64) $(LDLIBS)"
    "\n"
    "\nandroiddynamicall:	android32dynamicall android64dynamicall"
    "\n"
    "\nandroid32dynamicall: cleanandroid32dynamic builddirectories pch"
    "\n	@echo Building Android 32 bit executable"
    "\n	$(AND32GXX) $(ANDFLG) $(SRCFLS) -o $(ANDDYN32) $(LDLIBS)"
    "\n"
    "\nandroid32dynamic: cleanandroid32dynamic builddirectories"
    "\n	@echo Building Android 32 bit executable"
    "\n	$(AND32GXX) $(ANDFLG) $(SRCFLS) -o $(ANDDYN32) $(LDLIBS)"
    "\n"
    "\nandroid64dynamicall: cleanandroid64dynamic builddirectories pch"
    "\n	@echo Building Android 64 bit executable"
    "\n	$(AND64GXX) $(ANDFLG) $(SRCFLS) -o $(ANDDYN64) $(LDLIBS)"
    "\n"
    "\nandroid64dynamic: cleanandroid64dynamic builddirectories"
    "\n	@echo Building Android 64 bit executable"
    "\n	$(AND64GXX) $(ANDFLG) $(SRCFLS) -o $(ANDDYN64) $(LDLIBS)"
    "\n"
    "\ndebugdynamicall: cleandebugdynamic builddirectories pch buildallobjectslinux buildarchivelinux"
    "\n	@echo Building debug executable"
    "\n	$(CXX) $(GTKINC) -I$(INCDIR) -std=c++20 $(DBGFLG) $(SRCFLS) -o $(DBGDYN) $(LDLIBS) $(GTKLIB)"
    "\n"
    "\ndebugdynamic: builddirectories"
    "\n	@echo Building debug executable"
    "\n	$(CXX) $(GTKINC) -I$(INCDIR) $(DBGFLG) $(SRCFLS) -o $(DBGDYN) $(LDLIBS) $(GTKLIB)"
    "\n"
    "\ndebugstaticall: cleandebugstatic builddirectories pch buildlibslinux"
    "\n	@echo Building debug executable"
    "\n	$(CXX) $(STFLAG) $(GTKINC) -I$(INCDIR) -std=c++20 $(DBGFLG) $(SRCFLS) -o $(DBGSTC) $(LDLIBS) $(GTKLIB)"
    "\n"
    "\ndebugstatic: builddirectories"
    "\n	@echo Building debug executable"
    "\n	$(CXX) $(STFLAG) $(GTKINC) -I$(INCDIR) $(DBGFLG) $(SRCFLS) -o $(DBGSTC) $(GTKLIB) $(LDLIBS) $(GTKLIB)"
    "\n"
    "\ndebugbuilds: debugdynamic debugstatic"
    "\n"
    "\nreleasebuilds: releasedynamic releasestatic"
    "\n"
    "\nallbuilds: debugbuilds releasebuilds"
    "\n"
    "\n#.PHONY: all test clean"
    "\n"
    "\ntest:"
    "\n	@echo Running test of $(TSTEXE)"
    "\n	./$(TSTEXE) $(TSTARG)"
    "\n"
    "\nbuildlibslinux: buildallobjectslinux buildarchivelinux"
    "\n"
    "\nbuildlibsandroidarm32: buildallobjectsiandroidarm32 buildarchivelinux"
    "\n"
    "\nbuildlibsandroidaarch64: buildallobjectsandroidaarch64 buildarchivelinux"
    "\n"
    "\nbuildallobjectslinux: cleanobjects"
    "\n	@echo Building object files from $(INCDIR) to $(LIBDIR)"
    "\n	$(shell IFS=$(echo -en \"\\n\\b\") array=( $(OBJSRC) );\\"
    "\n		for file in \"$$ {array[@]}\";do \\"
    "\n			lib=$${file//include/lib}; \\"
    "\n			lib=$${lib//.cpp/.o}; \\"
    "\n			$(CXX) $(GTKINC) $(LDFLAG) -c $${file} -o $${lib} $(LDLIBS) $(GTKLIB); \\"
    "\n		done \\"
    "\n	)"
    "\n"
    "\nbuildallobjectsandroidarm32: cleanobjects"
    "\n	@echo Building object files from $(INCDIR) to $(LIBDIR)"
    "\n	$(shell IFS=$(echo -en \"\\n\\b\") array=( $(OBJSRC) );\\"
    "\n		for file in \"$$ {array[@]}\";do \\"
    "\n			lib=$${file//include/lib}; \\"
    "\n			lib=$${lib//.cpp/.o}; \\"
    "\n			$(AND32GXX) $(STFLAG) $(GTKINC) $(LDFLAG) -c $${file} -o $${lib} $(LDLIBS) $(GTKLIB); \\"
    "\n		done \\"
    "\n	)"
    "\n"
    "\nbuildallobjectsandroidaarch64: cleanobjects"
    "\n	@echo Building object files from $(INCDIR) to $(LIBDIR)"
    "\n	$(shell IFS=$(echo -en \"\\n\\b\") array=( $(OBJSRC) );\\"
    "\n		for file in \"$$ {array[@]}\";do \\"
    "\n			lib=$${file//include/lib}; \\"
    "\n			lib=$${lib//.cpp/.o}; \\"
    "\n			$(AND64GXX) $(STFLAG) $(GTKINC) $(LDFLAG) -c $${file} -o $${lib} $(LDLIBS) $(GTKLIB); \\"
    "\n		done \\"
    "\n	)"
    "\n"
    "\nbuildarchivelinux: cleanarchive"
    "\n	@echo Building object archive"
    "\n	ar rcs $(LIBDIR)/lib$(PROJNM).a $(OBJOBJ)"
    "\n"
    "\nbuilddirectories:"
    "\n	@echo Building project directories"
    "\n	$(shell \\"
    "\n	mkdir -p $(INCDIR) $(LIBDIR) \\"
    "\n	$(DBGDIR) $(RELDIR) $(ANDDIR) \\"
    "\n	$(DBGDYNDIR) $(DBGSTCDIR) \\"
    "\n	$(RELDYNDIR) $(RELSTCDIR) \\"
    "\n	$(ANDDIR) $(ANDDYNDIR) \\"
    "\n	$(ANDDYNDIR32) $(ANDDYNDIR64) \\"
    "\n	$(ANDSTCDIR) $(ANDSTCDIR32) \\"
    "\n	$(ANDSTCDIR64) \\"
    "\n	)"
    "\n"
    "\nbuilddirectoriestest:"
    "\n	mkdir -p $(TSTDYNDIR) $(TSTSTCDIR) $(TSTDIR)"
    "\n"
    "\ncleandirectories:"
    "\n	@echo Cleaning project directories"
    "\n	$(shell \\"
    "\n	rm -rf $(DBGDYNDIR) $(DBGSTCDIR) \\"
    "\n	$(RELDYNDIR) $(RELSTCDIR) \\"
    "\n	$(TSTDYNDIR) $(TSTSTCDIR) \\"
    "\n	$(ANDDIR) $(ANDDYNDIR) \\"
    "\n	$(ANDDYNDIR32) $(ANDDYNDIR64) \\"
    "\n	$(ANDSTCDIR) $(ANDSTCDIR32) \\"
    "\n	$(ANDSTCDIR64) \\"
    "\n	$(DBGDIR) $(TSTDIR) $(RELDIR) $(ANDDIR) \\"
    "\n	)"
    "\n"
    "\nclean: cleanpch cleandirectories cleanrelease cleandebug cleantest cleanobjects cleanarchive cleanandroid"
    "\n"
    "\ncleanpch:"
    "\n	rm -f $(PCHFIL).gch"
    "\n"
    "\ncleanrelease: cleanreleasedynamic cleanreleasestatic"
    "\n"
    "\ncleanreleasedynamic:"
    "\n	@echo Cleaning dynamic release"
    "\n	rm -f $(TGTDYN)"
    "\n"
    "\ncleanreleasestatic:"
    "\n	@echo Cleaning static release"
    "\n	rm -f $(TGTSTC)"
    "\n"
    "\ncleanandroid: cleanandroid32static cleanandroid64static cleanandroid32dynamic cleanandroid64dynamic"
    "\n"
    "\ncleanandroid32static:"
    "\n	@echo Cleaning static Android 32 bit release"
    "\n	rm -f $(ANDSTC32)"
    "\n"
    "\ncleanandroid64static:"
    "\n	@echo Cleaning static Android 64 bit release"
    "\n	rm -f $(ANDSTC64)"
    "\n"
    "\ncleanandroid32dynamic:"
    "\n	@echo Cleaning dynamic Android 32 bit release"
    "\n	rm -f $(ANDDYN32)"
    "\n"
    "\ncleanandroid64dynamic:"
    "\n	@echo Cleaning dynamic Android 64 bit release"
    "\n	rm -f $(ANDDYN64)"
    "\n"
    "\ncleandebug: cleandebugdynamic cleandebugstatic"
    "\n"
    "\ncleandebugdynamic:"
    "\n	@echo Cleaning dynamic debug"
    "\n	rm -f $(DBGDYN)"
    "\n"
    "\ncleandebugstatic:"
    "\n	@echo Cleaning static debug"
    "\n	rm -f $(DBGSTC)"
    "\n"
    "\ncleantest: cleantestdynamic cleanteststatic"
    "\n"
    "\ncleantestdynamic:"
    "\n	@echo Cleaning dynamic test"
    "\n	rm -f $(TSTDYN)"
    "\n"
    "\ncleanteststatic:"
    "\n	@echo Cleaning static test"
    "\n	rm -f $(TSTSTC)"
    "\n"
    "\ncleanobjects:"
    "\n	@echo Cleaning objects"
    "\n	rm -f $(LIBDIR)/*.o"
    "\n"
    "\ncleanarchive:"
    "\n	@echo Cleaning archive"
    "\n	rm -f $(LIBDIR)/*.a"
    "\n"
    "\ninstall: installdynamic"
    "\n"
    "\ninstalldynamic:"
    "\n	@echo Installing $(PROJNM)"
    "\n	cp -f $(TGTDYN) /usr/bin/$(PROJNM)"
    "\n"
    "\ninstallstatic:"
    "\n	@echo Installing $(PROJNM)"
    "\n	cp -f $(TGTSTC) /usr/bin/$(PROJNM)"
    "\n"
  );
}
std::string Globals::class_header_content_create(std::string class_name)
{
  std::transform(class_name.begin(), class_name.end(), class_name.begin(),
                 [](unsigned char chr)
  {
    return std::toupper(chr);
  });
  std::string content = "#ifndef ";
  content.append(class_name);
  content.append("\n#define ");
  content.append(class_name);
  content.append("\n");
  content.append("\n#endif \\\\ ");
  content.append(class_name);
  content.append("\n");
  return content;
}
std::string Globals::class_source_content_create(std::string class_file_name)
{
  std::string content = "#include \"";
  content.append(class_file_name);
  content.append(".h\"\n");
  return content;
}