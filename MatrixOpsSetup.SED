[Version]
Class=IEXPRESS
SEDVersion=3
[Options]
PackagePurpose=InstallApp
ShowInstallProgramWindow=0
HideExtractAnimation=0
UseLongFileName=1
InsideCompressed=0
CAB_FixedSize=0
CAB_ResvCodeSigning=0
RebootMode=N
InstallPrompt=%InstallPrompt%
DisplayLicense=%DisplayLicense%
FinishMessage=%FinishMessage%
TargetName=%TargetName%
FriendlyName=%FriendlyName%
AppLaunched=%AppLaunched%
PostInstallCmd=%PostInstallCmd%
AdminQuietInstCmd=%AdminQuietInstCmd%
UserQuietInstCmd=%UserQuietInstCmd%
SourceFiles=SourceFiles
[Strings]
InstallPrompt=
DisplayLicense=
FinishMessage=
TargetName=E:\Documents\MatrixOps\MatrixOpsSetup.EXE
FriendlyName=Matrix Operations
AppLaunched=cmd.exe /c "setup.bat"
PostInstallCmd=C:\Program Files\Hameer Abbasi\MatrixOps\MatrixOps.exe
AdminQuietInstCmd=
UserQuietInstCmd=
FILE0="MatrixOps.exe"
FILE1="vcredist_x86.exe"
FILE2="setup.bat"
[SourceFiles]
SourceFiles0=E:\Documents\MatrixOps\Release\
SourceFiles1=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Bootstrapper\Packages\vcredist_x86\
SourceFiles2=C:\Users\Hameer\Documents\
[SourceFiles0]
%FILE0%=
[SourceFiles1]
%FILE1%=
[SourceFiles2]
%FILE2%=
