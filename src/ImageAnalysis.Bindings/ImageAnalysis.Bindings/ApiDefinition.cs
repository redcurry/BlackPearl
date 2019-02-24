using System;

using ObjCRuntime;
using Foundation;
using UIKit;

namespace ImageAnalysis.Bindings
{
    [BaseType(typeof(NSObject))]
    interface ImageAnalysis
    {
        [Export("findCoin:")]
        NSArray<NSNumber> FindCoin(UIImage image);
    }
}

