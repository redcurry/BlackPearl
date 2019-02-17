using System;
using ObjCRuntime;

[assembly: LinkWith ("libImageAnalysis.a", LinkTarget.Simulator, ForceLoad = true, Frameworks = "Foundation")]
