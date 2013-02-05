
// BuyTicketDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BuyTicket.h"
#include "BuyTicketDlg.h"
#include "afxdialogex.h"
#include "Huoche.h"
#include "YzDlg.h"
#include <iostream>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBuyTicketDlg �Ի���

CHuoche *huoche;

CBuyTicketDlg::CBuyTicketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBuyTicketDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBuyTicketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
}

BEGIN_MESSAGE_MAP(CBuyTicketDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CBuyTicketDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBuyTicketDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_OPEN_URL, &CBuyTicketDlg::OnBnClickedOpenUrl)
	ON_STN_CLICKED(IDC_PIC, &CBuyTicketDlg::OnStnClickedPic)
	ON_BN_CLICKED(IDC_BLOG, &CBuyTicketDlg::OnBnClickedBlog)
END_MESSAGE_MAP()


// CBuyTicketDlg ��Ϣ��������

BOOL CBuyTicketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	huoche=new CHuoche(this);
	// TODO: �ڴ����Ӷ���ĳ�ʼ������
	if (huoche->GetCode())
	{
		this->LoadYzCode();
	}

	 std::ifstream userfile("c:\\buyticket.dat");
	 std::string  uname,upass,time,fromStation,toStation,date,name,id,phone,specialTrain;
        if(userfile.is_open())
        {
		std::getline(userfile,uname);
		std::getline(userfile,upass);
		std::getline(userfile,time);
		std::getline(userfile,fromStation);
		std::getline(userfile,toStation);
		std::getline(userfile,date);
		std::getline(userfile,name);
		std::getline(userfile,id);
		std::getline(userfile,phone);
		std::getline(userfile,specialTrain);
		userfile.close();

		this->GetDlgItem(IDC_UNAME)->SetWindowText(uname.c_str());
		this->GetDlgItem(IDC_UPASS)->SetWindowText(upass.c_str());
		
		this->GetDlgItem(IDC_FROMCITY)->SetWindowText(fromStation.c_str());
		this->GetDlgItem(IDC_TOCITY)->SetWindowText(toStation.c_str());
		this->GetDlgItem(IDC_DATE)->SetWindowText(date.c_str());

		this->GetDlgItem(IDC_FULLNAME)->SetWindowText(name.c_str());
		this->GetDlgItem(IDC_IDCARD)->SetWindowText(id.c_str());
		this->GetDlgItem(IDC_PHONE)->SetWindowText(phone.c_str());
		this->GetDlgItem(IDC_TRAIN)->SetWindowText(specialTrain.c_str());
	}

	if(time=="") time="5";
	this->GetDlgItem(IDC_EDIT_TIME)->SetWindowText(time.c_str());

	
	
	
	((CButton*)GetDlgItem(IDC_CHECK_YW))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_CHECK_EDZ))->SetCheck(TRUE);

	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBuyTicketDlg::OnPaint()
{
	LoadYzCode();
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBuyTicketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBuyTicketDlg::OnBnClickedButton1()
{
	CString code,name,pass;
	this->GetDlgItem(IDC_CODE)->GetWindowText(code);
	this->GetDlgItem(IDC_UNAME)->GetWindowText(name);
	this->GetDlgItem(IDC_UPASS)->GetWindowText(pass);
	std::string yzcode=code.GetBuffer();
	
	huoche->Login(name.GetBuffer(),pass.GetBuffer(),yzcode);
	
}


bool CBuyTicketDlg::LoadYzCode(void)
{
	CRect rect;
	this->GetDlgItem(IDC_PIC)->GetClientRect(&rect);     //m_pictureΪPicture Control�ؼ���������ÿؼ����������

	CImage image;       //ʹ��ͼƬ��
	image.Load("c:\\buyticket.png");   //װ��·����ͼƬ��Ϣ��ͼƬ��
	CDC* pDC = this->GetDlgItem(IDC_PIC)->GetWindowDC();    //�����ʾ�ؼ���DC
	image.Draw( pDC -> m_hDC,rect);      //ͼƬ���ͼƬ����Draw����
	
	ReleaseDC(pDC);
	return true;
}





void CBuyTicketDlg::OnBnClickedButton2()
{
	CString time;
	this->GetDlgItem(IDC_EDIT_TIME)->GetWindowText(time);

	int ntime=atoi(time)*1000;
	huoche->isInBuy=false;
	this->KillTimer(1);
	this->SetTimer(1,ntime,NULL);

	std::ofstream userfile("c:\\buyticket.dat");
	CString uname,upass,fromStation,toStation,date,name,id,phone,specialTrain;
	this->GetDlgItem(IDC_UNAME)->GetWindowText(uname);
	this->GetDlgItem(IDC_UPASS)->GetWindowText(upass);
	this->GetDlgItem(IDC_FROMCITY)->GetWindowText(fromStation);
	this->GetDlgItem(IDC_TOCITY)->GetWindowText(toStation);
	this->GetDlgItem(IDC_DATE)->GetWindowText(date);
	this->GetDlgItem(IDC_FULLNAME)->GetWindowText(name);
	this->GetDlgItem(IDC_IDCARD)->GetWindowText(id);
	this->GetDlgItem(IDC_PHONE)->GetWindowText(phone);
	this->GetDlgItem(IDC_TRAIN)->GetWindowText(specialTrain);

	userfile<<uname.GetBuffer()<<"\n";
	userfile<<upass.GetBuffer()<<"\n";
	userfile<<time.GetBuffer()<<"\n";
	userfile<<fromStation.GetBuffer()<<"\n";
	userfile<<toStation.GetBuffer()<<"\n";
	userfile<<date.GetBuffer()<<"\n";
	userfile<<name.GetBuffer()<<"\n";
	userfile<<id.GetBuffer()<<"\n";
	userfile<<phone.GetBuffer()<<"\n";
	userfile<<specialTrain.GetBuffer()<<"\n";

        userfile.close();
	
}


void CBuyTicketDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	CString fromcity,tocity,date,train;
	this->GetDlgItem(IDC_FROMCITY)->GetWindowText(fromcity);
	this->GetDlgItem(IDC_TOCITY)->GetWindowText(tocity);
	this->GetDlgItem(IDC_DATE)->GetWindowText(date);
	this->GetDlgItem(IDC_TRAIN)->GetWindowText(train);

	if(!huoche->isInBuy)
	{
		huoche->train=train.GetBuffer();
		huoche->SearchTicket(fromcity.GetBuffer(),tocity.GetBuffer(),date.GetBuffer());
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CBuyTicketDlg::OnBnClickedOpenUrl()
{
	ShellExecute(NULL, _T("open"), _T("iexplore"), _T("https://dynamic.12306.cn/otsweb/"), NULL, SW_SHOWNORMAL);
}


void CBuyTicketDlg::OnStnClickedPic()
{
	huoche->GetCode();
	this->LoadYzCode();
}


void CBuyTicketDlg::OnBnClickedBlog()
{
	ShellExecute(NULL, _T("open"), _T("http://www.xiaoqin.in/index.php?a=details&aid=110"),NULL, NULL, SW_SHOWNORMAL);
}