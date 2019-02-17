﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;

namespace BlackPearl.Xamarin
{
    public partial class MainPage : ContentPage
    {
        public MainPage()
        {
            InitializeComponent();

            Content = new Button
            {
                Text = DependencyService.Get<IImageAnalysis>().GetMean().ToString("f2")
            };
        }
    }
}
