//
// Created by unkown on 11/18/23.
//

#include "wx_frame.h"

wxIMPLEMENT_APP(wx_frame);

bool wx_frame::OnInit() {
    mainFrame *frame = new mainFrame();
    frame->Show();
    return true;
}

void mainFrame::Createeditor() {
    nbtext = new wxStyledTextCtrl(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,0,"");
    // Set margin type for line numbers
    nbtext->SetMarginType(1, wxSTC_MARGIN_NUMBER);
    nbtext->SetUseVerticalScrollBar(true);
    // Enable line number margin
    nbtext->SetMarginMask(1,0);

}

mainFrame::mainFrame() : wxFrame(nullptr, wxID_ANY, "Hello World",wxPoint(50,50),wxSize(800,600)){

    Sizer=new wxBoxSizer(wxVERTICAL);
    // Get the path to the executable
    wxString exePath = wxStandardPaths::Get().GetExecutablePath();
    // Extract the directory from the executable path
    wxString projectDir = wxPathOnly(exePath);

    // Navigate up one level to the project root
    wxString projectRoot = wxPathOnly(projectDir);

    // Construct the relative path to the icon file in the resources directory
    wxString iconPath = projectRoot + wxFILE_SEP_PATH + wxT("resources/myicon.png");

    wxIcon *icon=new wxIcon();
    icon->LoadFile(iconPath,wxBITMAP_TYPE_PNG);
    SetIcon(*icon);


    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN, "&Open...\tCtrl+O");
    menuFile->Append(wxID_SAVE,"&Save\tCtrl+S");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);


    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    Createeditor();
    Sizer->Add(nbtext,wxSizerFlags(1).Expand());
    Bind(wxEVT_MENU, &mainFrame::LoadContent, this, wxID_OPEN);
    Bind(wxEVT_MENU, &mainFrame::SaveContent, this, wxID_SAVE);
    Bind(wxEVT_MENU, &mainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &mainFrame::OnExit, this, wxID_EXIT);

    // Determine the maximum number of digits in your document
    int maxLineNumber = nbtext->GetLineCount();
    int digits = 1;
    while (maxLineNumber /= 10) {
        digits++;
    }

    int minWidth = nbtext->TextWidth(wxSTC_STYLE_LINENUMBER, "_999");
    int marginWidth = std::max(minWidth, nbtext->TextWidth(wxSTC_STYLE_LINENUMBER,  wxString::Format("%d", int(pow(10, digits)))) + 2);

    nbtext->SetMarginWidth(1,marginWidth);

    SetSizer(Sizer);
}

void mainFrame::LoadContent(wxCommandEvent& event)
{
    wxFileDialog
            openFileDialog(this, _("Open text file"), "", "",
                           "text files (*.txt)|*.txt|All files (*.*)|*.*|Cpp files (*.cpp)|*.cpp", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    fileName =openFileDialog.GetPath();
    wxTextFile file;
    if (file.Open(fileName)){
        wxString Content;
        for (int i = 0; i < file.GetLineCount(); ++i) {
            Content+=file.GetLine(i) +"\n";
        }
        nbtext->Clear();
        nbtext->SetValue(Content);
        file.Close();
    }
}

void mainFrame::SaveContent(wxCommandEvent& event){
    if (fileName ==""){
        wxFileDialog saveFileDialog(this,_("Save text file"),"","",
                                    "text files (*.txt)|*.txt",wxFD_SAVE);
        if (saveFileDialog.ShowModal()==wxID_CANCEL)
            return;
        fileName=saveFileDialog.GetPath();
    }
    wxTextFile file(fileName);
    if (!file.Exists())
        file.Create();
    if (file.Open()){
        file.Clear();
        file.AddLine(nbtext->GetValue());
        file.Write();
        file.Close();
    }
}

void mainFrame::OnExit(wxCommandEvent &event) {
    //delete nbtext;
    wxWindow::Close();
}

void mainFrame::OnAbout(wxCommandEvent &event) {
    wxMessageBox("This is Simple Text Editor",
                 "About", wxOK | wxICON_INFORMATION);
}

