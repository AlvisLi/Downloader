#include "stdafx.h"
#include "HttpCurl.h"
#include <assert.h>

HttpCurl::HttpCurl(void)
	: m_pCurl(NULL)
	, m_nPort(80)
	, m_hFile(INVALID_HANDLE_VALUE)
	, m_pCallback(NULL)
	, m_pCallbackParam(NULL)
	, m_curlCode(CURLE_OK)
	, m_lfFlag(HttpCurlFlag_None)
	, m_curlList(NULL)
	, m_bStopDownload(false)
{
	m_pCurl = curl_easy_init();
	curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA, this);
}


HttpCurl::~HttpCurl(void)
{
	ClearHeaderList();
	curl_easy_cleanup(m_pCurl);
	if ( m_hFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle(m_hFile);
	}
}

bool HttpCurl::SetPort( LONG port )
{
	if ( port == m_nPort ) 
		return true;
	m_nPort = port;
	m_curlCode = curl_easy_setopt(m_pCurl, CURLOPT_PORT, m_nPort);
	return CURLE_OK == m_curlCode;
}

bool HttpCurl::SetTimeout( int nSecond )
{
	if ( nSecond<0 )
		return false;
	m_curlCode = curl_easy_setopt(m_pCurl, CURLOPT_TIMEOUT, nSecond);
	
	return CURLE_OK == m_curlCode;
}

bool HttpCurl::SetConnectTimeout( int nSecond )
{
	if ( nSecond<0 )
		return false;
	m_curlCode = curl_easy_setopt(m_pCurl, CURLOPT_CONNECTTIMEOUT, nSecond);
	return CURLE_OK == m_curlCode;
}

bool HttpCurl::SetUserAgent( LPCSTR lpAgent )
{
	if ( NULL == lpAgent )
		return false;
	int nLen = static_cast<int>(strlen(lpAgent));
	if ( nLen == 0 )
		return false;
	m_curlCode = curl_easy_setopt(m_pCurl, CURLOPT_USERAGENT, lpAgent);
	return CURLE_OK == m_curlCode;
}

bool HttpCurl::SetResumeFrom( LONG lPos )
{
	if ( lPos<0 )
		return false;
	m_curlCode = curl_easy_setopt(m_pCurl, CURLOPT_RESUME_FROM, lPos);
	return CURLE_OK == m_curlCode;
}

bool HttpCurl::SetResumeFromLarge( LONGLONG llPos )
{
	if ( llPos<0 )
		return false;
	m_curlCode = curl_easy_setopt(m_pCurl, CURLOPT_RESUME_FROM_LARGE, llPos);
	return CURLE_OK == m_curlCode;
}

bool HttpCurl::AddHeader( LPCSTR lpKey, LPCSTR lpValue )
{
	assert(lpKey!=NULL && lpValue!=NULL);
	int nLen1 = static_cast<int>(strlen(lpKey)), nLen2 = static_cast<int>(strlen(lpValue));
	assert(nLen1>0 && nLen2>0);
	std::string strHeader(lpKey);
	strHeader.append(": ");
	strHeader.append(lpValue);
	m_curlList = curl_slist_append(m_curlList, strHeader.c_str());
	m_curlCode = curl_easy_setopt(m_pCurl, CURLOPT_HTTPHEADER, m_curlList);
	return CURLE_OK == m_curlCode;
}

void HttpCurl::ClearHeaderList()
{
	if ( m_curlList )
	{
		curl_slist_free_all(m_curlList);
		m_curlList = NULL;
	}
}

bool HttpCurl::SetCookie( LPCSTR lpCookie )
{
	assert(lpCookie!=NULL);
	m_curlCode = curl_easy_setopt(m_pCurl, CURLOPT_COOKIE, lpCookie);
	return CURLE_OK == m_curlCode;
}

bool HttpCurl::SetCookieFile( LPCSTR lpFilePath )
{
	assert(lpFilePath!=NULL);
	m_curlCode = curl_easy_setopt(m_pCurl, CURLOPT_COOKIEFILE, lpFilePath);
	return CURLE_OK == m_curlCode;
}

const char* HttpCurl::GetError() const
{
	return curl_easy_strerror(m_curlCode);
}

void HttpCurl::SetCallback( HttpCurlCallback* pCallback, void* lpParam )
{
	m_pCallbackParam = lpParam;
	m_pCallback = pCallback;
}

bool HttpCurl::DownloadToFile( LPCSTR lpUrl, LPCSTR lpFile )
{
	CURLcode code = curl_easy_setopt(m_pCurl, CURLOPT_URL, lpUrl);
	DeleteFileA(lpFile);
	m_hFile = CreateFileA(lpFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if ( INVALID_HANDLE_VALUE == m_hFile )
	{
		return FALSE;
	}
	curl_easy_setopt(m_pCurl, CURLOPT_NOPROGRESS, 0);
	curl_easy_setopt(m_pCurl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);
	curl_easy_setopt(m_pCurl, CURLOPT_PROGRESSDATA, this);
	m_lfFlag = HttpCurlFlag_Download;
	//开始执行请求
	m_curlCode = curl_easy_perform(m_pCurl);
	return CURLE_OK == m_curlCode;
}

bool HttpCurl::Delete(LPCSTR lpUrl, LPCSTR lpData)
{
	assert(lpData!=NULL);
	curl_easy_setopt(m_pCurl, CURLOPT_CUSTOMREQUEST,"delete");
	curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDS, lpData);
	//curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDSIZE, lpData);
	curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(m_pCurl, CURLOPT_URL, lpUrl);
	m_lfFlag = HttpCurlFlag_Delete;
	m_strRespons.clear();
	m_curlCode = curl_easy_perform(m_pCurl);
	return CURLE_OK == m_curlCode;
}


bool HttpCurl::Post( LPCSTR lpUrl, LPCSTR lpData )
{
	assert(lpData!=NULL);
	curl_easy_setopt(m_pCurl, CURLOPT_POST, 1);
	curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDS, lpData);
	//curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDSIZE, lpData);
	curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(m_pCurl, CURLOPT_URL, lpUrl);
	m_lfFlag = HttpCurlFlag_Post;
	m_strRespons.clear();
	m_curlCode = curl_easy_perform(m_pCurl);
	return CURLE_OK == m_curlCode;
}

bool HttpCurl::Post( LPCSTR lpUrl, unsigned char* lpData, unsigned int nSize )
{
	assert(lpData!=NULL && nSize>0);
	curl_easy_setopt(m_pCurl, CURLOPT_POST, 1);
	curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDS, lpData);
	curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDSIZE, nSize);
	curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(m_pCurl, CURLOPT_URL, lpUrl);
	m_lfFlag = HttpCurlFlag_Post;
	m_strRespons.clear();
	m_curlCode = curl_easy_perform(m_pCurl);
	return CURLE_OK == m_curlCode;
}

bool HttpCurl::Get( LPCSTR lpUrl )
{
	assert(lpUrl!=NULL);
	curl_easy_setopt(m_pCurl, CURLOPT_HTTPGET, 1);
	curl_easy_setopt(m_pCurl, CURLOPT_URL, lpUrl);
	curl_easy_setopt(m_pCurl, CURLOPT_FOLLOWLOCATION, 1);//支持重定向
	curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(m_pCurl, CURLOPT_FRESH_CONNECT, TRUE);
	curl_easy_setopt(m_pCurl, CURLOPT_DNS_USE_GLOBAL_CACHE, 0);

	AddHeader("Cache-Control", "no-cache");
	AddHeader("Cache-Control", "max-age=0");

	m_lfFlag = HttpCurlFlag_Get;
	m_strRespons.clear();
	m_curlCode = curl_easy_perform(m_pCurl);
	return CURLE_OK == m_curlCode;
}

const std::string& HttpCurl::GetRespons() const
{
	return m_strRespons;
}

const char* HttpCurl::GetResponsPtr() const
{
	return m_strRespons.c_str();
}

double HttpCurl::GetDownloadSpeed()
{
	if (m_curlCode == CURLE_OK)
	{
		double speed;
		m_curlCode = curl_easy_getinfo(m_pCurl, CURLINFO_SPEED_DOWNLOAD, &speed);
		if (m_curlCode == CURLE_OK)
		{
			return speed;
		}
		else
		{
			return 0;
		}
	}

	return 0;
}

bool HttpCurl::AddForm(curl_httppost** httpPostPtr, curl_httppost** lastPostPtr, const char* formName, const char* formContent)
{
	//CURLFORM_COPYNAME, "status", text
	curl_formadd(
				httpPostPtr, 
				lastPostPtr, 
				CURLFORM_COPYNAME, formName,
				CURLFORM_COPYCONTENTS, formContent,
				CURLFORM_END
				);

	return true;
}

bool HttpCurl::AddBinaryForm(curl_httppost** httpPostPtr, curl_httppost** lastPostPtr, const char* formName, const char* formContent, const char* formContentType)
{
	//std::wstring formContentW;
	//ConvertUtf8ToUnicode(formContent, formContentW);
	//if(FALSE == PathFileExists(formContentW.c_str()))
	//	return false;

	//HANDLE imageFileHandle = CreateFile(formContentW.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//if(INVALID_HANDLE_VALUE == imageFileHandle)
	//	return false;

	//DWORD imageSize = GetFileSize(imageFileHandle, NULL);
	//if(0 == imageSize)
	//	return false;

	//char* imageBuffer = new char[imageSize];
	//DWORD numberOfByteRead = 0;
	//ReadFile(imageFileHandle, imageBuffer, imageSize, &numberOfByteRead, NULL);
	//if(numberOfByteRead != imageSize)
	//{
	//	CloseHandle(imageFileHandle);
	//	return false;
	//}

	//CloseHandle(imageFileHandle);

	//curl_formadd(
	//	httpPostPtr, 
	//	lastPostPtr, 
	//	CURLFORM_COPYNAME, formName,
	//	CURLFORM_BUFFER, formContent,
	//	CURLFORM_BUFFERPTR, imageBuffer,
	//	CURLFORM_BUFFERLENGTH, imageSize,
	//	CURLFORM_CONTENTTYPE, formContentType,//"image/png",
	//	CURLFORM_END
	//	);

	return true;
}

bool HttpCurl::PostForm(const char* url, std::list<FORM_INFO*>& formList)
{
	if(0 == formList.size())
		return false;

	struct curl_httppost* httpPostPtr = NULL;
	struct curl_httppost* lastPostPtr = NULL;

	std::list<char*> bufferList;
	auto iterForm = formList.begin();
	while(iterForm != formList.end())
	{
		FORM_INFO* formInfoPtr = *iterForm;
		if(formInfoPtr)
		{
			switch(formInfoPtr->formType)
			{
			case FORM_TYPE_NORMAL:
				AddForm(&httpPostPtr, &lastPostPtr, formInfoPtr->formName.c_str(), formInfoPtr->formContent.c_str());
				break;

			case FORM_TYPE_BINARY:
				if(AddBinaryForm(&httpPostPtr, &lastPostPtr, formInfoPtr->formName.c_str(), formInfoPtr->formContent.c_str(), formInfoPtr->formContentType.c_str()))
				{
					if(lastPostPtr && lastPostPtr->buffer)
						bufferList.push_back(lastPostPtr->buffer);
				}
				break;

			default:
				break;
			}
		}

		iterForm++;
	}

	curl_easy_setopt(m_pCurl, CURLOPT_HTTPPOST, httpPostPtr);
	curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(m_pCurl, CURLOPT_URL, url);

	m_lfFlag = HttpCurlFlag_Post;
	m_strRespons.clear();
	m_curlCode = curl_easy_perform(m_pCurl);

	curl_formfree(httpPostPtr);
	auto iterBuffer = bufferList.begin();
	while(iterBuffer != bufferList.end())
	{
		if(*iterBuffer)
			delete [] *iterBuffer;

		iterBuffer++;
	}
	bufferList.clear();

	return m_curlCode == CURLE_OK;
}

void HttpCurl::StopDownload()
{
	m_bStopDownload = true;
}

size_t HttpCurl::WriteCallback( void* pBuffer, size_t nSize, size_t nMemByte, void* pParam )
{
	//把下载到的数据以追加的方式写入文件(一定要有a，否则前面写入的内容就会被覆盖了)
	HttpCurl* pThis = (HttpCurl*)pParam;
	DWORD dwWritten = 0;
	switch( pThis->m_lfFlag )
	{
	case HttpCurlFlag_Download://下载
	{
		if (pThis->m_bStopDownload)
		{
			return 0;
		}

		if (pThis->m_hFile == INVALID_HANDLE_VALUE)
			return 0;
		if (!WriteFile(pThis->m_hFile, pBuffer, static_cast<DWORD>(nSize*nMemByte), &dwWritten, NULL))
			return 0;
	}
		break;
	case HttpCurlFlag_Post://Post数据
	case HttpCurlFlag_Get://Get数据
		{
			pThis->m_strRespons.append((const char*)pBuffer, nSize*nMemByte);
			dwWritten = static_cast<DWORD>(nSize*nMemByte);
		}
		break;
	case HttpCurlFlag_None://未定义
		break;
	}
	return dwWritten;
}

size_t HttpCurl::HeaderCallback( void* pBuffer, size_t nSize, size_t nMemByte, void* pParam )
{
	HttpCurl* pThis = (HttpCurl*)pParam;
	return 0;
}

int HttpCurl::ProgressCallback( void *pParam, double dltotal, double dlnow, double ultotal, double ulnow )
{
	HttpCurl* pThis = (HttpCurl*)pParam;
	if ( pThis->m_pCallback )
	{
		pThis->m_pCallback->HttpCurlProgress(pThis->m_pCallbackParam, dltotal, dlnow);
	}
	return 0;
}
