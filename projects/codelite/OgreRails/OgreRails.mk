##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=OgreRails
ConfigurationName      :=Debug
IntermediateDirectory  :=../../../bin
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/sterlyn/projects/cpp/OgreRails/projects/codelite"
ProjectPath            := "/home/sterlyn/projects/cpp/OgreRails/projects/codelite/OgreRails"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Sterlyn K9
Date                   :=08/29/2011
CodeLitePath           :="/home/sterlyn/.codelite"
LinkerName             :=gcc
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=gcc
C_CompilerName         :=gcc
OutputFile             :=../../../bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/sterlyn/projects/cpp/OgreRails/projects/codelite/OgreRails/OgreRails.txt"
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
C_CmpOptions           := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/usr/include/OGRE 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)OgreMain $(LibrarySwitch)OIS $(LibrarySwitch)stdc++ $(LibrarySwitch)m 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/lib/ $(LibraryPathSwitch)/usr/lib64/ 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/src_Application$(ObjectSuffix) $(IntermediateDirectory)/src_Main$(ObjectSuffix) $(IntermediateDirectory)/path_CurveSegment$(ObjectSuffix) $(IntermediateDirectory)/path_SegmentGraphicFactory$(ObjectSuffix) $(IntermediateDirectory)/util_DebugConsole$(ObjectSuffix) $(IntermediateDirectory)/util_UniqueIdGenerator$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

makeDirStep:
	@test -d ../../../bin || $(MakeDirCommand) ../../../bin

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_Application$(ObjectSuffix): ../../../src/Application.cpp $(IntermediateDirectory)/src_Application$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sterlyn/projects/cpp/OgreRails/src/Application.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Application$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Application$(DependSuffix): ../../../src/Application.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Application$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Application$(DependSuffix) -MM "/home/sterlyn/projects/cpp/OgreRails/src/Application.cpp"

$(IntermediateDirectory)/src_Application$(PreprocessSuffix): ../../../src/Application.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Application$(PreprocessSuffix) "/home/sterlyn/projects/cpp/OgreRails/src/Application.cpp"

$(IntermediateDirectory)/src_Main$(ObjectSuffix): ../../../src/Main.cpp $(IntermediateDirectory)/src_Main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sterlyn/projects/cpp/OgreRails/src/Main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_Main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Main$(DependSuffix): ../../../src/Main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Main$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Main$(DependSuffix) -MM "/home/sterlyn/projects/cpp/OgreRails/src/Main.cpp"

$(IntermediateDirectory)/src_Main$(PreprocessSuffix): ../../../src/Main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Main$(PreprocessSuffix) "/home/sterlyn/projects/cpp/OgreRails/src/Main.cpp"

$(IntermediateDirectory)/path_CurveSegment$(ObjectSuffix): ../../../src/path/CurveSegment.cpp $(IntermediateDirectory)/path_CurveSegment$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sterlyn/projects/cpp/OgreRails/src/path/CurveSegment.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/path_CurveSegment$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/path_CurveSegment$(DependSuffix): ../../../src/path/CurveSegment.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/path_CurveSegment$(ObjectSuffix) -MF$(IntermediateDirectory)/path_CurveSegment$(DependSuffix) -MM "/home/sterlyn/projects/cpp/OgreRails/src/path/CurveSegment.cpp"

$(IntermediateDirectory)/path_CurveSegment$(PreprocessSuffix): ../../../src/path/CurveSegment.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/path_CurveSegment$(PreprocessSuffix) "/home/sterlyn/projects/cpp/OgreRails/src/path/CurveSegment.cpp"

$(IntermediateDirectory)/path_SegmentGraphicFactory$(ObjectSuffix): ../../../src/path/SegmentGraphicFactory.cpp $(IntermediateDirectory)/path_SegmentGraphicFactory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sterlyn/projects/cpp/OgreRails/src/path/SegmentGraphicFactory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/path_SegmentGraphicFactory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/path_SegmentGraphicFactory$(DependSuffix): ../../../src/path/SegmentGraphicFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/path_SegmentGraphicFactory$(ObjectSuffix) -MF$(IntermediateDirectory)/path_SegmentGraphicFactory$(DependSuffix) -MM "/home/sterlyn/projects/cpp/OgreRails/src/path/SegmentGraphicFactory.cpp"

$(IntermediateDirectory)/path_SegmentGraphicFactory$(PreprocessSuffix): ../../../src/path/SegmentGraphicFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/path_SegmentGraphicFactory$(PreprocessSuffix) "/home/sterlyn/projects/cpp/OgreRails/src/path/SegmentGraphicFactory.cpp"

$(IntermediateDirectory)/util_DebugConsole$(ObjectSuffix): ../../../src/util/DebugConsole.cpp $(IntermediateDirectory)/util_DebugConsole$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sterlyn/projects/cpp/OgreRails/src/util/DebugConsole.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/util_DebugConsole$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/util_DebugConsole$(DependSuffix): ../../../src/util/DebugConsole.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/util_DebugConsole$(ObjectSuffix) -MF$(IntermediateDirectory)/util_DebugConsole$(DependSuffix) -MM "/home/sterlyn/projects/cpp/OgreRails/src/util/DebugConsole.cpp"

$(IntermediateDirectory)/util_DebugConsole$(PreprocessSuffix): ../../../src/util/DebugConsole.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/util_DebugConsole$(PreprocessSuffix) "/home/sterlyn/projects/cpp/OgreRails/src/util/DebugConsole.cpp"

$(IntermediateDirectory)/util_UniqueIdGenerator$(ObjectSuffix): ../../../src/util/UniqueIdGenerator.cpp $(IntermediateDirectory)/util_UniqueIdGenerator$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sterlyn/projects/cpp/OgreRails/src/util/UniqueIdGenerator.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/util_UniqueIdGenerator$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/util_UniqueIdGenerator$(DependSuffix): ../../../src/util/UniqueIdGenerator.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/util_UniqueIdGenerator$(ObjectSuffix) -MF$(IntermediateDirectory)/util_UniqueIdGenerator$(DependSuffix) -MM "/home/sterlyn/projects/cpp/OgreRails/src/util/UniqueIdGenerator.cpp"

$(IntermediateDirectory)/util_UniqueIdGenerator$(PreprocessSuffix): ../../../src/util/UniqueIdGenerator.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/util_UniqueIdGenerator$(PreprocessSuffix) "/home/sterlyn/projects/cpp/OgreRails/src/util/UniqueIdGenerator.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/src_Application$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Application$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Application$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_Main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_Main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_Main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/path_CurveSegment$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/path_CurveSegment$(DependSuffix)
	$(RM) $(IntermediateDirectory)/path_CurveSegment$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/path_SegmentGraphicFactory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/path_SegmentGraphicFactory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/path_SegmentGraphicFactory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/util_DebugConsole$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/util_DebugConsole$(DependSuffix)
	$(RM) $(IntermediateDirectory)/util_DebugConsole$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/util_UniqueIdGenerator$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/util_UniqueIdGenerator$(DependSuffix)
	$(RM) $(IntermediateDirectory)/util_UniqueIdGenerator$(PreprocessSuffix)
	$(RM) $(OutputFile)


