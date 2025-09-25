using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows;

namespace VecApp
{
    public class TreeItemTemplateSelector : DataTemplateSelector
    {
        public DataTemplate SensitivityTemplate { get; set; }
        public DataTemplate LuminosityMaskTemplate { get; set; }
        public DataTemplate LuminosityMaskTemplate2 { get; set; }
        public DataTemplate DistanceMaskTemplate1 { get; set; }
        public DataTemplate DistanceMaskTemplate2 { get; set; }
        public DataTemplate PointCloudCorrectionTemplate { get; set; }
        public DataTemplate LuminanceSliceTemplate { get; set; }
        public DataTemplate SensitivitySliceTemplate { get; set; }
        public DataTemplate GuideLaserPowerTemplate { get; set; }
        public DataTemplate InterpolationTemplate { get; set; }
        public DataTemplate AngleMaskTemplate { get; set; }
        public DataTemplate TwoPeakMaskTemplate { get; set; }
        public DataTemplate EdgeMaskTemplate { get; set; }
        public DataTemplate MemoTemplate { get; set; }
        public DataTemplate DefaultTemplate { get; set; }

        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            if (item is TreeItem treeItem)
            {
                return treeItem.UIType switch
                {
                    "Sensitivity" => SensitivityTemplate,
                    "LuminosityMask" => LuminosityMaskTemplate,
                    "LuminosityMask2" => LuminosityMaskTemplate2,
                    "DistanceMask1" => DistanceMaskTemplate1,
                    "DistanceMask2" => DistanceMaskTemplate2,
                    "PointCloudCorrection" => PointCloudCorrectionTemplate,
                    "LuminanceSlice" => LuminanceSliceTemplate,
                    "SensitivitySlice" => SensitivitySliceTemplate,
                    "GuideLaserPower" => GuideLaserPowerTemplate,
                    "Interpolation" => InterpolationTemplate,
                    "AngleMask" => AngleMaskTemplate,
                    "TwoPeakMask" => TwoPeakMaskTemplate,
                    "EdgeMask" => EdgeMaskTemplate,
                    "Memo" => MemoTemplate,
                    _ => DefaultTemplate
                };
            }
            return base.SelectTemplate(item, container);
        }
    }
}
