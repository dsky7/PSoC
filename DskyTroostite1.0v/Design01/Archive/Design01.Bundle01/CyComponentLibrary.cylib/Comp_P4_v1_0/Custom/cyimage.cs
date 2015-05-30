/*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/


using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace Comp_P4_v1_0
{
    class CyImage : IDisposable
    {
        #region Input parameters fields
        public CyHysteresisType m_hysteresis = CyHysteresisType.CMP_ENABLE_HYST;
        public CyPolarityType m_polarity;
        public CyPowerType m_power;
        #endregion Input parameters fields

        #region Image related fields
        public Size m_imageSize;
        public Bitmap m_bmp;
        #endregion Image related fields

        #region Private fields
        private bool m_isDisposed = false;
        #endregion Private fields

        #region Constructor(s)
        public CyImage()
        {
            m_imageSize = new Size(100, 100);
        }
        #endregion Constructor(s)

        #region Dispose
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        protected virtual void Dispose(bool disposing)
        {
            if (!m_isDisposed)
            {
                if (disposing)
                {
                    if (m_bmp != null)
                        m_bmp.Dispose();
                }
            }
            m_isDisposed = true;
        }
        #endregion Dispose

        #region Update image
        /// <summary>
        /// This function draws the symbol that is displayed on the right side of the window
        /// </summary>
        public void UpdateSymbol()
        {
            m_bmp = new Bitmap(m_imageSize.Width, m_imageSize.Height);
            Size defSize = new Size(100, 100);
            int triangleLeft = m_imageSize.Width / 5;
            int triangleRight = m_imageSize.Width - triangleLeft;
            int triangleSide = (int)((triangleRight - triangleLeft) / Math.Cos(Math.PI/6));
            int triangleTop = m_imageSize.Height / 2 - triangleSide / 2;
            int triangleBottom = triangleTop + triangleSide;
            int plusY = triangleTop + triangleSide / 3;
            int minusY = triangleTop + 2 * triangleSide / 3;
            int plusCenterX = triangleLeft + triangleSide / 6;
            int plusW = (plusCenterX - triangleLeft) * 4 / 3;
            int hystLeft = triangleLeft + (plusCenterX - triangleLeft) * 2;
            int hystW = plusW / 3;

            Pen pen = new Pen(Color.Black, 1);
            Pen penPlus = new Pen(Color.Black, 2);
            Pen penWire = new Pen(Color.FromArgb(0, 0, 128), 1);
            Brush brushAqua = Brushes.Aqua;
            Brush brushWhite = Brushes.White;

            using (Graphics g = Graphics.FromImage(m_bmp))
            {
                g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;

                // triangle
                Point[] pts = new Point[3];
                pts[0] = new Point(triangleLeft, triangleTop);
                pts[1] = new Point(triangleLeft, triangleBottom);
                pts[2] = new Point(triangleRight, triangleTop + triangleSide / 2);
                g.FillPolygon(brushAqua, pts);
                g.DrawPolygon(pen, pts);

                // lines
                g.DrawLine(penWire, new Point(0, plusY), new Point(triangleLeft, plusY));
                g.DrawLine(penWire, new Point(0, minusY), new Point(triangleLeft, minusY));
                g.DrawLine(penWire, new Point(triangleRight, triangleTop + triangleSide / 2), 
                                    new Point(m_imageSize.Width, triangleTop + triangleSide / 2));

                // plus, minus
                g.DrawLine(penPlus, new Point(plusCenterX - plusW / 2, plusY), 
                                    new Point(plusCenterX + plusW / 2, plusY));
                g.DrawLine(penPlus, new Point(plusCenterX, plusY - plusW / 2), 
                                    new Point(plusCenterX, plusY + plusW / 2));
                g.DrawLine(penPlus, new Point(plusCenterX - plusW / 2, minusY),
                                    new Point(plusCenterX + plusW / 2, minusY));

                // invert
                if (m_polarity == CyPolarityType.CMP_INVERTING)
                {
                    g.FillEllipse(brushWhite, pts[2].X, pts[2].Y - triangleLeft / 4, triangleLeft / 2, 
                                              triangleLeft / 2);
                    g.DrawEllipse(pen, pts[2].X, pts[2].Y - triangleLeft / 4, triangleLeft / 2, triangleLeft / 2);
                }
                
                // hysteresis
                if (m_hysteresis == CyHysteresisType.CMP_ENABLE_HYST)
                {
                    g.DrawLine(pen, new Point(hystLeft, plusY), new Point(hystLeft + hystW * 2, plusY));
                    g.DrawLine(pen, new Point(hystLeft + hystW, minusY), new Point(hystLeft + hystW * 3, minusY));
                    g.DrawLine(pen, new Point(hystLeft + hystW, plusY), new Point(hystLeft + hystW, minusY));
                    g.DrawLine(pen, new Point(hystLeft + 2 * hystW, plusY), new Point(hystLeft + 2 * hystW, minusY));
                }
            }
            pen.Dispose();
            penPlus.Dispose();
            penWire.Dispose();
        }

        /// <summary>
        /// This function draws a graph that is displayed at the bottom of the window
        /// </summary>
        public void UpdateGraph()
        {
            m_bmp = new Bitmap(m_imageSize.Width, m_imageSize.Height);
            Size defSize = new Size(410, 150);
            float scaleX = m_imageSize.Width / (float)defSize.Width;
            float scaleY = m_imageSize.Height / (float)defSize.Height;
            int startX = 40;
            int endX = 400;
            int startY = 10;
            int vddaY = 20;
            int hystY = 45;
            int vminY = 50;
            int vplusY = 70;
            int ovY = 75;
            int dashStartY = 35;
            int dashEndY = 96;
            
            int blueW = (endX - startX) / 4;
            int blueCrossX = (int)(blueW * ((float)(vplusY - vminY) / (vplusY - vddaY)));
            int blueCrossHystX = (int)(blueW * ((float)(vplusY - hystY) / (vplusY - vddaY)));
            int hystTextX = 45;
            int hystArrH = 15;
            int waveShift = 9;
            int waveY1 = 100;
            int waveY2 = 140;

            using (Graphics g = Graphics.FromImage(m_bmp))
            {
                g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;

                g.ScaleTransform(scaleX, scaleY);

                g.Clear(Color.White);
                Brush blkbrush = Brushes.Black;
                Brush greenbrush = Brushes.Green;
                Brush bluebrush = Brushes.Blue;
                Brush orangebrush = Brushes.Orange;
                Pen extentspen = new Pen(blkbrush);
                Pen greenpen = new Pen(greenbrush);
                Pen bluepen = new Pen(bluebrush);
                Pen orangepen = new Pen(orangebrush);
                extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                // Setup the input wave 
                g.DrawLine(extentspen, startX, vddaY, endX, vddaY);
                g.DrawLine(greenpen, startX, vminY, endX, vminY);
                g.DrawLine(extentspen, startX, ovY, endX, ovY);
                extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
                g.DrawLine(extentspen, startX, startY, startX, m_imageSize.Height);

                // blue line
                Point[] bluePts = new Point[5];
                for (int i = 0; i < bluePts.Length; i++)
                {
                    bluePts[i].Y = (i % 2 == 0) ? vplusY : vddaY;
                    bluePts[i].X = startX + i * blueW;
                }
                g.DrawLines(bluepen, bluePts);

                // hysteresis horizontal line
                if (m_hysteresis == CyHysteresisType.CMP_ENABLE_HYST)
                {
                    g.DrawLine(greenpen, startX, hystY, endX, hystY);
                    
                    extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                    extentspen.StartCap = System.Drawing.Drawing2D.LineCap.ArrowAnchor;
                    g.DrawLine(extentspen, hystTextX, hystY, hystTextX, hystY - hystArrH);
                    g.DrawLine(extentspen, hystTextX, vminY, hystTextX, vminY + hystArrH);

                    using (Font arrow = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel))
                    {
                        g.DrawString("10mV", arrow, blkbrush, hystTextX, hystY - hystArrH);
                    }
                    extentspen.StartCap = System.Drawing.Drawing2D.LineCap.Flat;
                }

                int[] ptsLineX = new int[8];

                // dash vertical
                extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                for (int i = 0; i < 4; i++)
                {
                    int shift = (m_hysteresis == CyHysteresisType.CMP_ENABLE_HYST) ? blueCrossHystX : blueCrossX;
                    int crossX = (i % 2 == 0) ? bluePts[i].X + shift : bluePts[i + 1].X - blueCrossX;
                    g.DrawLine(extentspen, crossX, dashStartY, crossX, dashEndY);
                    ptsLineX[i * 2] = crossX;
                    ptsLineX[i * 2 + 1] = crossX;
                }
                g.DrawLines(bluepen, bluePts);

                // output square wave
                Point[] orangePts = new Point[10];

                int yUp = (m_polarity == CyPolarityType.CMP_INVERTING) ? waveY2 : waveY1;
                int yLow = (m_polarity == CyPolarityType.CMP_INVERTING) ? waveY1 : waveY2;
                if (m_power == CyPowerType.CMP_LOW_POWER)
                {
                    waveShift *= 2;

                }
                else if (m_power == CyPowerType.CMP_HIGH_POWER)
                {
                    waveShift = 0;
                }
                orangePts[0] = new Point(startX, yLow);
                orangePts[9] = new Point(endX, yLow);
                for (int i = 0; i < ptsLineX.Length; i++)
                {
                    int y = yLow;
                    int x = ptsLineX[i];
                    if ((i % 4 == 1) || (i % 4 == 2))
                    {
                        y = yUp;
                    }
                    x += (i % 2 == 0) ? -waveShift : waveShift;

                    orangePts[i + 1] = new Point(x, y);
                }
                g.DrawLines(orangepen, orangePts);

                int txtX = 7;
                int txtVX = 17;
                int txtYstart = 95;
                int txtStepY = 20;
                int txtH = 10;

                Font perfont = new Font("Arial", 10, FontStyle.Regular, GraphicsUnit.Pixel);
                g.DrawString("Vdda", perfont, blkbrush, new PointF(txtX, vddaY - txtH));
                g.DrawString("0V", perfont, blkbrush, new PointF(txtVX, vplusY));
                g.DrawString("Vddd", perfont, blkbrush, new PointF(txtX, txtYstart));
                g.DrawString("Vssd", perfont, blkbrush, new PointF(txtX, txtYstart + 2 * txtStepY));
                g.DrawString("V+", perfont, bluebrush, new PointF(txtVX, vplusY - txtH));
                g.DrawString("V-", perfont, greenbrush, new PointF(txtVX, vminY - txtH));
                g.DrawString("out", perfont, greenbrush, new PointF(txtVX, txtYstart + txtStepY));
                
                perfont.Dispose();
                extentspen.Dispose();
                greenpen.Dispose();
                bluepen.Dispose();
                orangepen.Dispose();

                g.ResetTransform();
            }
        }
        #endregion Update image
    }
}
