using System;
using System.Windows;
using System.Windows.Controls;

namespace VecApp
{
    /// <summary>
    /// Panel Types
    /// </summary>
    public enum Panel
    {
        None,
        Initialize,
        ProbeSetting,
        ThresholdSetting,
        SensorConnection,
        ProbeInput,
        _0AxisInitialize,
        Inspection,
        GaugeSetting,
        Setting,
        ContactInspection,
        ContactProperty,
        ContactSelfJudgment,
        ArmTypeSetting,
        ArmNetworkSetting,
        ApiScan,
        NonContactSelfJudgment,
        SensorNetworkSetting,
    }

    /// <summary>
    /// Base class for Panel
    /// </summary>
    public abstract class PanelBase : UserControl
    {
        private SubWindowBase _parent;

        private Panel _type;

        public PanelBase(SubWindowBase parent, Panel type)
        {
            _parent = parent;
            _type = type;
        }

        public virtual void Terminate()
        {
        }

        public SubWindowBase Parent
        {
            get => _parent;
        }

        public Panel Type
        {
            get => _type;
        }
    }
}
