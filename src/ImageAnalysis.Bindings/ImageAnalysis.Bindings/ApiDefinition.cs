using System;

using ObjCRuntime;
using Foundation;
using UIKit;

namespace ImageAnalysis.Bindings
{
    [BaseType(typeof(NSObject))]
    interface ImageAnalysis
    {
        [Export("drawOn:")]
        UIImage DrawOn(UIImage image);
    }
}

