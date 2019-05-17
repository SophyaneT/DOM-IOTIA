using Android.Bluetooth;
using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;

namespace ProjectMobileDOM
{
    public partial class MainPage : ContentPage
    {

        public MainPage()
        {
            InitializeComponent();
        }

        private async void ChangePageAsync(object sender, EventArgs e)
        {
            if (Username.Text == "admin" && Pwd.Text == "admin")
                await Navigation.PushModalAsync(new Home());
            else
                errorPwd.IsVisible = true;

        }
        public void Button_Clicked(object sender, EventArgs e)
        {
          
        }
    }
}
