-- premake5.lua
workspace "WolfensteinClone"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "WolfensteinClone"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "WolfensteinClone"