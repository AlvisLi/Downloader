#ifndef IT_DATA_DEF_H
#define IT_DATA_DEF_H

#include <memory>
#include <string>

namespace ITData
{
	typedef struct tagDownloadAppInfo
	{
		std::string appName; //�������
		std::string logoUrl;  //���logo���ص�ַ
		std::string logoLocalPath; //���logo���ش�ŵ�ַ
		std::string appUrl; //������ص�ַ
		std::string appLocalPath; //������ش�ŵ�ַ
		std::string	appDownloadComplete;	//�����Ƿ����״̬,���Ϊ"1"
		int			appDownloadTimeOrder;
		int			appDownloadProgress;	//���ؽ��ȣ���Χ0-100���������������ڴ�
	}ITDownloadAppInfo;
	typedef std::shared_ptr<ITDownloadAppInfo> ITDownloadAppPtr;
}

#endif //IT_DATA_DEF_H
