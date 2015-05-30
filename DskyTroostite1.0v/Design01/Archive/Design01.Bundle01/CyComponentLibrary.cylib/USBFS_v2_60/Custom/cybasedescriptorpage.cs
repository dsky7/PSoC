/*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using CyDesigner.Extensions.Common;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace USBFS_v2_60
{
    public partial class CyBaseDescriptorPage : CyEditingWrapperControl
    {
        #region Const

        private const int TREE_LEVEL_ROOT = 0;
        private const int TREE_LEVEL_INTERFACEGEN = 1;
        private const int TREE_LEVEL_INTERFACE = 2;
        private const int TREE_LEVEL_CLASS_SPEC = 3;
        private const int TREE_LEVEL_EP_SPEC = 4;

        protected const string LISTVIEW_GROUP_INTERACE = "groupInterface";
        protected const string LISTVIEW_GROUP_AC = "groupAC";
        protected const string LISTVIEW_GROUP_AS = "groupAS";
        protected const string LISTVIEW_GROUP_AC2 = "groupAC2";
        protected const string LISTVIEW_GROUP_AS2 = "groupAS2";
        protected const string LISTVIEW_GROUP_MS = "groupMS";
        protected const string LISTVIEW_GROUP_COMM = "groupCommunications";

        protected const string LISTVIEW_GROUP_ENDPOINT = "groupEndpoint";
        #endregion Const

        #region Variables

        protected List<CyUSBDescriptor> m_ItemsList;
        private CyDescriptorTree m_descTree;
        private CyUSBDescriptorType m_descType;
        private string m_descText;
        private string m_nodekeyBase;
        private int m_imageIndexSpec = 6;
        private TreeNode m_mouseSelectedNode;

        #endregion Variables

        //------------------------------------------------------------------------------------------------------------

        #region Constructors

        public CyBaseDescriptorPage()
        {
            InitializeComponent();
        }

        public CyBaseDescriptorPage(CyUSBFSParameters parameters, CyUSBDescriptorType pageDescType)
            : base(parameters)
        {
            InitializeComponent();

            m_descType = pageDescType;
            InitClassDependentFields();

            InitItems();
            RefreshDescriptorTree();

            labelListName.Text = m_descText + " Descriptors List";
        }

        #endregion Constructors

        //------------------------------------------------------------------------------------------------------------

        #region Private functions

        private void InitClassDependentFields()
        {
            switch (m_descType)
            {
                case CyUSBDescriptorType.AUDIO:
                    m_descTree = m_parameters.m_audioTree;
                    m_descText = "Audio";
                    m_nodekeyBase = CyUSBFSParameters.NODEKEY_AUDIO;
                    m_imageIndexSpec = 6;
                    break;
                case CyUSBDescriptorType.MIDI:
                    m_descTree = m_parameters.m_midiTree;
                    m_descText = "Midi";
                    m_nodekeyBase = CyUSBFSParameters.NODEKEY_MIDI;
                    m_imageIndexSpec = 6;
                    break;
                case CyUSBDescriptorType.CDC:
                    m_descTree = m_parameters.m_cdcTree;
                    m_descText = "CDC";
                    m_nodekeyBase = CyUSBFSParameters.NODEKEY_CDC;
                    m_imageIndexSpec = 7;
                    break;
                default:
                    Debug.Assert(false);
                        break;
            }
        }

        /// <summary>
        /// Initializes m_reportItems list and fills listBoxItems listBox.
        /// </summary>
        protected virtual void InitItems()
        {
            m_ItemsList = new List<CyUSBDescriptor>();
        }

        private void RefreshDescriptorTree()
        {
            treeViewDesc.BeginUpdate();
            treeViewDesc.Nodes.Clear();
            for (int i = 0; i < m_descTree.m_nodes.Count; i++)
            {
                CyDescriptorNode descriptor = m_descTree.m_nodes[i];
                TreeNode node = treeViewDesc.Nodes.Add(descriptor.Key,
                                                         CyDescriptorNode.GetDescriptorLabel(descriptor), 0, 0);
                RefreshNode(descriptor, node);
            }

            treeViewDesc.ExpandAll();
            treeViewDesc.EndUpdate();
        }

        private void RefreshNode(CyDescriptorNode descriptor, TreeNode treeNode)
        {
            int imageIndex = 0;
            for (int i = 0; i < descriptor.m_nodes.Count; i++)
            {
                CyDescriptorNode descriptor_child = descriptor.m_nodes[i];
                TreeNode node;
                
                switch (descriptor_child.m_value.bDescriptorType)
                {
                    case CyUSBDescriptorType.ENDPOINT:
                    case CyUSBDescriptorType.CS_ENDPOINT:
                    case CyUSBDescriptorType.ALTERNATE:
                    case CyUSBDescriptorType.INTERFACE:
                    case CyUSBDescriptorType.AUDIO:
					case CyUSBDescriptorType.CDC:
                        imageIndex = m_imageIndexSpec;
                        break;
                    default:
                        break;
                }
                
                // Find a place to insert the node
                if ((descriptor_child.m_value.bDescriptorType == CyUSBDescriptorType.AUDIO) ||
                    (descriptor_child.m_value.bDescriptorType == CyUSBDescriptorType.CDC))
                {
                    int nodeIndex = 0;
                    for (int j = 0; j < descriptor.m_nodes.IndexOf(descriptor_child); j++)
                    {
                        if ((descriptor.m_nodes[j].m_value.bDescriptorType == CyUSBDescriptorType.AUDIO) ||
                            (descriptor.m_nodes[j].m_value.bDescriptorType == CyUSBDescriptorType.CDC))
                        {
                            nodeIndex++;
                        }
                    }
                    node = treeNode.Nodes.Insert(nodeIndex, descriptor_child.Key,
                                                 CyDescriptorNode.GetDescriptorLabel(descriptor_child), imageIndex,
                                                 imageIndex);
                }
                else
                    node = treeNode.Nodes.Add(descriptor_child.Key,
                                              CyDescriptorNode.GetDescriptorLabel(descriptor_child), imageIndex,
                                              imageIndex);
                
                RefreshNode(descriptor_child, node);
            }
        }

        private void AddNewNode(CyUSBDescriptor item)
        {
            if (item == null) return;
            
            CyDescriptorNode parentNode, newNode;
            if (item is CyInterfaceDescriptor)
            {
                if (treeViewDesc.SelectedNode != null)
                {
                    if (treeViewDesc.SelectedNode.Level == TREE_LEVEL_ROOT)
                        parentNode = GetParentDescriptorAtLevel(TREE_LEVEL_ROOT);
                    else
                        parentNode = GetParentDescriptorAtLevel(TREE_LEVEL_INTERFACEGEN);
                }
                else parentNode = null;

            }
            else if (item is CyASEndpointDescriptor)
            {
                parentNode = GetParentDescriptorAtLevel(TREE_LEVEL_CLASS_SPEC);
            }
            else
            {
                parentNode = GetParentDescriptorAtLevel(TREE_LEVEL_INTERFACE);
            }

            newNode = new CyDescriptorNode(item);

            if (parentNode != null)
            {
                if (parentNode.Key == m_nodekeyBase) // Create general interface descriptor first
                {
                    // generate name for interface general descriptor
                    int newIndex = parentNode.m_nodes.Count + 1;
                    CyDescriptorNode generalInterfaceNode =
                        new CyDescriptorNode(new CyInterfaceGeneralDescriptor(
                                             String.Format("{0} Interface {1}", m_descText, newIndex)));
                    generalInterfaceNode.Key = generalInterfaceNode.Key.Replace(CyUSBFSParameters.NODEKEY_USBDESCRIPTOR,
                                                      CyUSBFSParameters.NODEKEY_INTERFACE);
                    parentNode.m_nodes.Add(generalInterfaceNode);
                    parentNode = parentNode.m_nodes[parentNode.m_nodes.Count - 1];
                }
                parentNode.m_nodes.Add(newNode);

                RefreshDescriptorTree();
                treeViewDesc.SelectedNode = treeViewDesc.Nodes.Find(newNode.Key, true)[0];
            }
        }

        private CyDescriptorNode GetParentDescriptorAtLevel(int level)
        {
            CyDescriptorNode selectedItem = null;
            TreeNode node;
            if (treeViewDesc.SelectedNode != null)
            {
                node = treeViewDesc.SelectedNode;
                while ((node.Level > 0) && (node.Level > level))
                    node = node.Parent;
                selectedItem = m_descTree.GetNodeByKey(node.Name);
            }
            return selectedItem;
        }

        /// <summary>
        /// Displays the information about the selected node of treeViewReport in the setting panel
        /// </summary>
        private void ShowEditItem()
        {
            if (treeViewDesc.SelectedNode == null) return;

            CyDescriptorNode selectedItem = m_descTree.GetNodeByKey(treeViewDesc.SelectedNode.Name);
            CyUSBDescriptor descItem;
            if ((selectedItem != null) && (treeViewDesc.SelectedNode.Level > TREE_LEVEL_INTERFACEGEN))
            {
                descItem = selectedItem.m_value;
                propertyGrid.SelectedObject = descItem;
                //Change label text
                labelItemProperties.Text = string.Format("Item Value ({0})", descItem.ToString().Trim());
                splitContainerDetails.Panel2.BackColor = SystemColors.Control;
            }
            else
            {
                propertyGrid.SelectedObject = null;
                if (selectedItem != null)
                {
                    labelItemProperties.Text = string.Format("Item Value ({0})", "");
                    splitContainerDetails.Panel2.BackColor = SystemColors.Control;
                }
            }
        }

        private void TreeViewSelection()
        {
            if (treeViewDesc.SelectedNode == null) return;

            toolStripButtonRemove.Enabled = treeViewDesc.SelectedNode.Level > TREE_LEVEL_ROOT;

            bool includeInterface = true, includeAC = false, includeAS = false, includeEP = false, includeASEP = false;
            switch (treeViewDesc.SelectedNode.Level)
            {
                case TREE_LEVEL_ROOT:
                    break;
                case TREE_LEVEL_INTERFACEGEN:
                    break;
                case TREE_LEVEL_INTERFACE:
                case TREE_LEVEL_CLASS_SPEC:
                case TREE_LEVEL_EP_SPEC:
                    CyDescriptorNode interfaceNode = GetParentDescriptorAtLevel(TREE_LEVEL_INTERFACE);
                    CyDescriptorNode currNode = m_descTree.GetNodeByKey(treeViewDesc.SelectedNode.Name);
                    if (interfaceNode != null)
                    {
                        includeAC = IncludeACListItems(interfaceNode);
                        includeAS = IncludeASListItems(interfaceNode);
                        includeASEP = IncludeASEPListItems(interfaceNode, currNode);
                        includeEP = true;
                    }
                    break;
                default:
                    break;
            }

            FillListViewItems(includeInterface, includeAC, includeAS, includeEP, includeASEP);

            if (treeViewDesc.SelectedNode.Level > TREE_LEVEL_INTERFACEGEN)
            {
                listViewDescList.SelectedItems.Clear();
                ShowEditItem();
            }
            else if (listViewDescList.SelectedIndices.Count == 0)
            {
                ShowEditItem();
            }

            if (listViewDescList.SelectedIndices.Count > 0)
                buttonApply.Enabled = true;
            else
            {
                buttonApply.Enabled = false;
            }
        }

        protected virtual bool IncludeACListItems(CyDescriptorNode interfaceNode)
        {
            return false;
        }

        protected virtual bool IncludeASListItems(CyDescriptorNode interfaceNode)
        {
            return false;
        }

        protected virtual bool IncludeASEPListItems(CyDescriptorNode interfaceNode, CyDescriptorNode selectedNode)
        {
            return false;
        }

        protected virtual void FillListViewItems(bool includeInterface, bool includeAC, bool includeAS, bool includeEP,
                                       bool includeASEP)
        {
            Debug.Assert(false);
        }

        private void RemoveTreeItem()
        {
            if (treeViewDesc.SelectedNode == null) return;

            TreeNode treeNode = treeViewDesc.SelectedNode;
            TreeNode prevNode = treeNode.PrevNode;
            if (prevNode == null)
                prevNode = treeNode.Parent;

            if (treeNode.Level == TREE_LEVEL_ROOT) return;

            TreeNode parent = treeNode.Parent;
            if (parent != null)
                m_descTree.RemoveNode(treeNode.Name, parent.Name);

            ParamTreeChanged();
            RefreshDescriptorTree();
            //Select previous node
            if (prevNode != null)
                treeViewDesc.SelectedNode = treeViewDesc.Nodes.Find(prevNode.Name, true)[0];
        }

        public static void ChangePropertyGridBrowsAttr(PropertyGrid propertyGrid)
        {
            if ((propertyGrid.SelectedObject != null) && propertyGrid.SelectedObject is CyEndpointDescriptor)
            {
                CyEndpointDescriptor desc = propertyGrid.SelectedObject as CyEndpointDescriptor;
                desc.UpdateBrowsableItems();
            }
        }

        private void ParamTreeChanged()
        {
            if (m_descTree == m_parameters.m_audioTree)
            {
                m_parameters.ParamAudioTreeChanged();
            }
            else if (m_descTree == m_parameters.m_midiTree)
            {
                m_parameters.ParamMidiTreeChanged();
            }
            else if (m_descTree == m_parameters.m_cdcTree)
            {
                m_parameters.ParamCDCTreeChanged();
            }
        }

        #endregion Private functions

        #region Events

        private void CyBaseDescriptorPage_VisibleChanged(object sender, EventArgs e)
        {
            if (Visible)
                RefreshDescriptorTree();
        }

        private void buttonApply_Click(object sender, EventArgs e)
        {
            if (listViewDescList.SelectedIndices.Count == 0) return;

            // Add to the tree
            AddNewNode((CyUSBDescriptor)propertyGrid.SelectedObject);

            ParamTreeChanged();
        }

        private void treeViewDesc_AfterSelect(object sender, TreeViewEventArgs e)
        {
            TreeViewSelection();
        }

        private void treeViewDesc_Enter(object sender, EventArgs e)
        {
            TreeViewSelection();
        }

        private void toolStripButtonRemove_Click(object sender, EventArgs e)
        {
            RemoveTreeItem();
        }

        private void treeViewDesc_BeforeLabelEdit(object sender, NodeLabelEditEventArgs e)
        {
            // Allow only editing of titles and comments.
            if (IsNodeEditable(e.Node) == false)
            {
                e.CancelEdit = true;
            }
        }

        private void treeViewDesc_AfterLabelEdit(object sender, NodeLabelEditEventArgs e)
        {
            if (treeViewDesc.SelectedNode == null)
                return;
            CyDescriptorNode node = m_descTree.GetNodeByKey(treeViewDesc.SelectedNode.Name);
            if (e.Label == null)
            {
                treeViewDesc.SelectedNode.Text = ((CyInterfaceGeneralDescriptor)node.m_value).DisplayName;
            }
            else if ((node.m_value is CyInterfaceGeneralDescriptor) && 
                     (((CyInterfaceGeneralDescriptor)node.m_value).DisplayName != e.Label))
            {
                ((CyInterfaceGeneralDescriptor)node.m_value).DisplayName = e.Label;
                ParamTreeChanged();
            }
        }

        #region DragNDrop
        private void treeViewDesc_ItemDrag(object sender, ItemDragEventArgs e)
        {
            if ((e.Item is TreeNode) && (((TreeNode)e.Item).Level > TREE_LEVEL_ROOT))
                DoDragDrop(e.Item, DragDropEffects.Move);
        }

        private void treeViewDesc_DragEnter(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.Move;
        }

        private TreeNode m_oldNode;

        private void treeViewDesc_DragOver(object sender, DragEventArgs e)
        {
            Point pt = ((TreeView) sender).PointToClient(new Point(e.X, e.Y));
            TreeNode aNode = ((TreeView) sender).GetNodeAt(pt);
            if ((aNode != null) && (e.Data.GetDataPresent(CyUSBFSParameters.TYPE_TREE_NODE, false)))
            {
                // If the node is a folder, change the color of the background to dark blue to simulate selection
                // Be sure to return the previous node to its original color by copying from a blank node
                if ((m_oldNode != null) && (m_oldNode != aNode))
                {
                    m_oldNode.BackColor = treeViewDesc.Nodes[0].BackColor;
                    m_oldNode.ForeColor = treeViewDesc.Nodes[0].ForeColor;
                }
                TreeNode dragNode = (TreeNode)e.Data.GetData(CyUSBFSParameters.TYPE_TREE_NODE);
                if ((aNode.Level == dragNode.Level) || (aNode.Level == dragNode.Level - 1))
                {
                    aNode.BackColor = Color.LightBlue;
                    aNode.ForeColor = Color.White;
                    m_oldNode = aNode;
                }
            }
            if ((m_oldNode != null) && (m_oldNode != aNode))
            {
                m_oldNode.BackColor = treeViewDesc.Nodes[0].BackColor;
                m_oldNode.ForeColor = treeViewDesc.Nodes[0].ForeColor;
            }
        }

        private void treeViewDesc_DragLeave(object sender, EventArgs e)
        {
            if (m_oldNode != null)
            {
                m_oldNode.BackColor = treeViewDesc.Nodes[0].BackColor;
                m_oldNode.ForeColor = treeViewDesc.Nodes[0].ForeColor;
            }
        }

        private void treeViewDesc_DragDrop(object sender, DragEventArgs e)
        {
            if (m_oldNode != null)
            {
                m_oldNode.BackColor = treeViewDesc.Nodes[0].BackColor;
                m_oldNode.ForeColor = treeViewDesc.Nodes[0].ForeColor;
            }

            if (e.Data.GetDataPresent(CyUSBFSParameters.TYPE_TREE_NODE, false))
            {
                Point pt = ((TreeView) sender).PointToClient(new Point(e.X, e.Y));
                TreeNode destinationNode = ((TreeView) sender).GetNodeAt(pt);
                TreeNode newNode = (TreeNode)e.Data.GetData(CyUSBFSParameters.TYPE_TREE_NODE);
                TreeNode sourceParent = newNode.Parent;
                TreeNode destParent;
                
                if (destinationNode == null)
                    return;

                if (destinationNode.Level == newNode.Level)
                {
                    destParent = destinationNode.Parent;
                }
                else if (destinationNode.Level == newNode.Level - 1)
                {
                    destParent = destinationNode;
                }
                // return if levels are not correspondent
                else return;

                if (destinationNode != newNode)
                {
                    CyDescriptorNode sourceDesc = m_descTree.GetNodeByKey(newNode.Name);
                    CyDescriptorNode destinationDesc = m_descTree.GetNodeByKey(destinationNode.Name);
                    CyDescriptorNode sourceParentDesc = m_descTree.GetNodeByKey(sourceParent.Name);
                    CyDescriptorNode destParentDesc = m_descTree.GetNodeByKey(destParent.Name);

                    if ((sourceDesc != null) && (destinationDesc != null) && 
                        (sourceParentDesc != null) && (destParent != null) &&
                        (destParent.Level == sourceParent.Level))
                    {
                        sourceParentDesc.m_nodes.Remove(sourceDesc);
                        if (destinationNode == destParent)
                            destParentDesc.m_nodes.Add(sourceDesc);
                        else
                            destParentDesc.m_nodes.Insert(destParentDesc.m_nodes.IndexOf(destinationDesc), sourceDesc);

                        ParamTreeChanged();
                        RefreshDescriptorTree();
                        treeViewDesc.SelectedNode = treeViewDesc.Nodes.Find(newNode.Name, true)[0];
                    }
                }
            }
        }
        #endregion DragNDrop

        private void treeViewReport_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                RemoveTreeItem();
            }
        }

        private void listViewDescList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listViewDescList.SelectedIndices.Count > 0)
            {
                propertyGrid.SelectedObject =
                    m_ItemsList[Convert.ToInt32(listViewDescList.SelectedItems[0].Tag)].Clone();
                buttonApply.Enabled = true;
                splitContainerDetails.Panel2.BackColor = Color.LightSteelBlue;
                labelItemProperties.Text = string.Format("Item Value ({0})", propertyGrid.SelectedObject.
                                                                             ToString().Trim());
            }
        }

        private void propertyGrid_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            // Update String Descriptor information if string was changed
            if (e.ChangedItem.Label.StartsWith("i"))
            {
                uint strIndex = m_parameters.SaveStringDescriptor(e.ChangedItem.Value.ToString());
                m_parameters.RefreshStringsDropDownList();
                try
                {
                    Type objType = propertyGrid.SelectedObject.GetType();
                    string fName = e.ChangedItem.Label.Remove(0, 1).Insert(0, "iw");
                    FieldInfo fi = objType.GetField(fName);
                    if (fi != null)
                    {
                        fi.SetValue(propertyGrid.SelectedObject, strIndex);
                    }
                }
                catch (Exception ex)
                {
                    Debug.Assert(false, ex.ToString());
                }
            }
            else if (e.ChangedItem.Label == "bAlternateSetting")
            {
                TreeNode node = treeViewDesc.SelectedNode;
                if (node != null)
                    node.Text = CyDescriptorNode.GetDescriptorLabel(m_descTree.GetNodeByKey(node.Name));
            }
            propertyGrid.Refresh();
            ParamTreeChanged();
        }

        private void propertyGrid_SelectedObjectsChanged(object sender, EventArgs e)
        {
            ChangePropertyGridBrowsAttr(propertyGrid);
            m_parameters.RefreshStringsDropDownList();
        }

        private void toolStripButtonSave_Click(object sender, EventArgs e)
        {
            CyDescriptorNode descNode = GetParentDescriptorAtLevel(TREE_LEVEL_INTERFACEGEN);
            if (descNode != null)
            {
                m_parameters.SaveDescriptorList(descNode, m_descType);
            }
        }

        private void toolStripButtonImport_Click(object sender, EventArgs e)
        {
            if (m_parameters.ImportDescriptorList(m_descType))
            {
                m_parameters.ParamStringTreeChanged();
                ParamTreeChanged();
            }
            RefreshDescriptorTree();
        }

        #endregion Events

        #region ProcessCmdKey() override
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == (Keys.Control | Keys.S))
            {
                if (toolStripButtonSave.Enabled && toolStripButtonSave.Visible)
                {
                    toolStripButtonSave_Click(null, new EventArgs());
                }
                return true;
            }
            else if (keyData == (Keys.Control | Keys.O))
            {
                if (toolStripButtonImport.Enabled && toolStripButtonImport.Visible)
                {
                    toolStripButtonImport_Click(null, new EventArgs());
                }
                return true;
            }
            else
                return base.ProcessCmdKey(ref msg, keyData);
        }
        #endregion ProcessCmdKey() override

        #region Rename option in context menu of tree
        private void treeViewDesc_MouseDown(object sender, MouseEventArgs e)
        {
            m_mouseSelectedNode = treeViewDesc.GetNodeAt(e.X, e.Y);
        }

        private void contextMenuStripTree_Opening(object sender, CancelEventArgs e)
        {
            if (IsNodeEditable(m_mouseSelectedNode) == false)
            {
                e.Cancel = true;
                return;
            }
            if (m_mouseSelectedNode == null)
            {
                e.Cancel = true;
                return;
            }
            treeViewDesc.SelectedNode = m_mouseSelectedNode;
        }

        private void renameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (m_mouseSelectedNode != null)
            {
                if (!m_mouseSelectedNode.IsEditing)
                {
                    m_mouseSelectedNode.BeginEdit();
                }
            }
        }

        public static bool IsNodeEditable(TreeNode node)
        {
            if (node == null)
                return false;

            // Allow only editing of the interface (or report) titles and comments.
            if ((((node.Level == TREE_LEVEL_INTERFACEGEN) ||
                 ((node.Level > TREE_LEVEL_INTERFACEGEN) && (CyUSBFSParameters.StringIsComment(node.Text))))))
            {
                return true;
            }
            return false;
        }
        #endregion Rename option in context menu of tree
    }
}
