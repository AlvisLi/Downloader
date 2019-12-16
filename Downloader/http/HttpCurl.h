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
	std::string formContent;     //二进制时为文件路径
	std::string formContentType; //二进制时为文件类型 image/gif
}FORM_INFO;

class HttpCurl
{
public:
	HttpCurl(void);
	~HttpCurl(void);
	/******************************************************************************
	*封装类的外部调用接口
	*/
	bool SetPort(LONG port);											//设置连接端口号
	bool SetTimeout(int nSecond);										//设置执行超时（秒）
	bool SetConnectTimeout(int nSecond);								//设置连接超时（秒）
	bool SetUserAgent(LPCSTR lpAgent);									//设置用户代理
	bool SetResumeFrom(LONG lPos);										//设置断点续传起始位置
	bool SetResumeFromLarge(LONGLONG llPos);							//设置断点续传起始位置，针对大文件
	bool AddHeader(LPCSTR lpKey, LPCSTR lpValue);						//添加自定义头
	void ClearHeaderList();												//清理HTTP列表头
	bool SetCookie(LPCSTR lpCookie);									//设置HTTP请求cookie
	bool SetCookieFile(LPCSTR lpFilePath);								//设置HTTP请求cookie文件
	const char* GetError()const;										//获取错误详细信息
	void SetCallback(HttpCurlCallback* pCallback, void* lpParam);		//设置下载进度回调
	bool DownloadToFile(LPCSTR lpUrl, LPCSTR lpFile);		 			//下载文件到磁盘
	bool Post(LPCSTR lpUrl, LPCSTR lpData);								//Post 字符串数据
	bool Post(LPCSTR lpUrl, unsigned char* lpData, unsigned int nSize); //Post 字符串或者二进制数据
	bool PostForm(const char* url, std::list<FORM_INFO*>& formList);
	bool Delete(LPCSTR lpUrl, LPCSTR lpData);	                        //Delete
	bool Get(LPCSTR lpUrl);												//Get 请求

	const std::string& GetRespons()const;									//获取Post/Get请求返回数据
	const char*	GetResponsPtr()const;									//获取Post/Get请求返回数据
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