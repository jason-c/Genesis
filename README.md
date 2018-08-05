   ______                     _     
  / ____/__  ____  ___  _____(_)____
 / / __/ _ \/ __ \/ _ \/ ___/ / ___/
/ /_/ /  __/ / / /  __(__  ) (__  ) 
\____/\___/_/ /_/\___/____/_/____/ 


------------------------------------------------------------------------

To Get Started

------------------------------------------------------------------------

Download and install Visual Studio Community 2017 (Version 15.7.5)
https://visualstudio.microsoft.com/downloads/
Create an account for Visual Studio and sign in when launching Visual Studio for the first time

Download and install Unreal Engine 4 (Version 4.19.2)
https://www.unrealengine.com/en-US/download
Launch the Epic Games Launcher.
Create an epic account and sign in.
Click the Unreal Engine Tab.
Click Install Unreal Engine button
After installing. The button will change to Launch Unreal Engine.
Click the button to launch then close. I needed to do this to get windows to associate uproject files with UE4.

Download and install GitKraken
https://www.gitkraken.com/download
Create a GitHub account and ask jason-c to add you to the project
Launch GetKraken
File->Clone Repo->Clone with URL
Where to clone to: Choose a spot to put the project on your hard drive
URL: https://github.com/jason-c/Genesis

------------------------------------------------------------------------

To Build The Project and Play the Game

------------------------------------------------------------------------

Locate the place you cloned the repository to and got to the UE4Project folder
Right click UEProject.uproject->Generate Visual Studio project files
You'll want to do this whenever sync to the project to ensure that the project has any newly added files
In the same folder, double click UE4Project.sln to open the project in Visual Studio
Build->Build Solution (Ctrl+Shift+B)
Wait for the build to finish.
If the build fails, let a programmer know.
Back in the folder where you launch the Visual Studio project, Double click UEProject.uproject to launch the project in UE4
Click the Play button near the top of the window