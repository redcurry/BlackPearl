using System;
using ObjCRuntime;

[assembly: LinkWith ("opencv2.a", LinkTarget.ArmV7 | LinkTarget.ArmV7s | LinkTarget.Simulator, ForceLoad = true, LinkerFlags = "-lc++")]
