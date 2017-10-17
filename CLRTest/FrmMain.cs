using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using EarthCLR;

namespace CLRTest
{
    public partial class FrmMain : Form
    {
        private EarthRender earthRender;

        public FrmMain()
        {
            InitializeComponent();

            earthRender = new EarthRender();
        }

        private void FrmMain_Load(object sender, EventArgs e)
        {
            earthRender.initEarth((Int32)this.panel1.Handle);

            earthRender.startRender();
        }
    }
}
