using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Xamarin.Forms;

namespace BlackPearl.Xamarin
{
    public interface IImageAnalysis
    {
        Stream DrawOn(byte[] jpg);
    }
}
