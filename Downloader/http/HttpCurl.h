#ifndef HTTPCURL_H
#define HTTPCURL_H

#include "curl/curl.h"
#include <string>
#include <list>

class HttpCurlCallback
{
public:
	virtual int HttpCurlProgress(void* pParam, double total, double downloaded) = 0;
};

enum HttpCurlFlag
{
	HttpCurlFlag_None = 0,
	HttpCurlFlag_Download,
	HttpCurlFlag_Post,
	HttpCurlFlag_Get,
	HttpCurlFlag_Delete
};

typedef enum _tagFormType
{
	FORM_TYPE_NORMAL,
	FORM_TYPE_BINARY
}FORM_TYPE;

typedef struct _tagFormInfo
{
	_tagFormInfo()
	{
		formType = FORM_TYPE_NORMAL;
	}

	FORM_TYPE   formType;
	std::string formName;
	std::string formContent;     //������ʱΪ�ļ�·��
	std::string formContentType; //������ʱΪ�ļ����� image/gif
}FORM_INFO;

class HttpCurl
{
public:
	HttpCurl(void);
	~HttpCurl(void);
	/******************************************************************************
	*��װ����ⲿ���ýӿ�
	*/
	bool SetPort(LONG port);											//�������Ӷ˿ں�
	bool SetTimeout(int nSecond);										//����ִ�г�ʱ���룩
	bool SetConnectTimeout(int nSecond);								//�������ӳ�ʱ���룩
	bool SetUserAgent(LPCSTR lpAgent);									//�����û�����
	bool SetResumeFrom(LONG lPos);										//���öϵ�������ʼλ��
	bool SetResumeFromLarge(LONGLONG llPos);							//���öϵ�������ʼλ�ã���Դ��ļ�
	bool AddHeader(LPCSTR lpKey, LPCSTR lpValue);						//����Զ���ͷ
	void ClearHeaderList();												//����HTTP�б�ͷ
	bool SetCookie(LPCSTR lpCookie);									//����HTTP����cookie
	bool SetCookieFile(LPCSTR lpFilePath);								//����HTTP����cookie�ļ�
	const char* GetError()const;										//��ȡ������ϸ��Ϣ
	void SetCallback(HttpCurlCallback* pCallback, void* lpParam);		//�������ؽ��Ȼص�
	bool DownloadToFile(LPCSTR lpUrl, LPCSTR lpFile);		 			//�����ļ�������
	bool Post(LPCSTR lpUrl, LPCSTR lpData);								//Post �ַ�������
	bool Post(LPCSTR lpUrl, unsigned char* lpData, unsigned int nSize); //Post �ַ������߶���������
	bool PostForm(const char* url, std::list<FORM_INFO*>& formList);
	bool Delete(LPCSTR lpUrl, LPCSTR lpData);	                        //Delete
	bool Get(LPCSTR lpUrl);												//Get ����

	const std::string& GetRespons()const;									//��ȡPost/Get���󷵻�����
	const char*	GetResponsPtr()const;									//��ȡPost/Get���󷵻�����
	double GetDownloadSpeed();
	void StopDownload();

protected:
	bool AddForm(curl_httppost** httpPostPtr, curl_httppost** lastPostPtr, const char* formName, const char* formContent);
	bool AddBinaryForm(curl_httppost** httpPostPtr, curl_httppost** lastPostPtr, const char* formName, const char* formContent, const char* formContentType);

	static size_t	WriteCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam);
	static size_t	HeaderCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam);
	static int		ProgressCallback(void *pParam, double dltotal, double dlnow, double ultotal, double ulnow);

private:
	CURL*               m_pCurl;
	LONG				m_nPort;
	HANDLE				m_hFile;
	CURLcode			m_curlCode;
	std::string			m_strRespons;
	HttpCurlFlag			m_lfFlag;
	curl_slist*			m_curlList;
	void*               m_pCallbackParam;
	HttpCurlCallback*   m_pCallback;
	bool				m_bStopDownload;
};



#endif //HTTPCURL_H