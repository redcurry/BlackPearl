using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Xamarin.Forms;

namespace BlackPearl.Xamarin
{
    public interface IImageAnalysis
    {
        Coin FindCoin(byte[] jpg);
    }

    public class Coin
    {
        public double X { get; set; }
        public double Y { get; set; }
        public double Radius { get; set; }
    }
}
