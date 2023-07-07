using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Intento1_ET
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = "COM11";
                serialPort1.Open();
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Close();
                }
                catch (Exception error)
                {
                    MessageBox.Show(error.Message);
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //try
            //{
            //    serialPort1.Open();
            //}
            //catch (Exception error)
            //{
            //    MessageBox.Show(error.Message);
            //}
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            while (serialPort1.IsOpen && serialPort1.BytesToRead > 0)
            {
                string serialData = serialPort1.ReadLine();

                int value = Convert.ToInt32(serialData);

                if (value >= circularProgressBar1.Minimum && value <= circularProgressBar1.Maximum)
                {
                    circularProgressBar1.Text = serialData;
                    circularProgressBar1.Value = value;
                }
            }
        }
    }
}
