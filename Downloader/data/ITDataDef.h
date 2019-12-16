#ifndef IT_DATA_DEF_H
#define IT_DATA_DEF_H

#include <memory>
#include <string>

namespace ITData
{
	typedef struct tagDownloadAppInfo
	{
		std::string appName; //软件名称
		std::string logoUrl;  //软件logo下载地址
		std::string logoLocalPath; //软件logo本地存放地址
		std::string appUrl; //软件下载地址
		std::string appLocalPath; //软件本地存放地址
		std::string	appDownloadComplete;	//下载是否完成状态,完成为"1"
		int			appDownloadTimeOrder;
		int			appDownloadProgress;	//下载进度（范围0-100），仅仅保存在内存
	}ITDownloadAppInfo;
	typedef std::shared_ptr<ITDownloadAppInfo> ITDownloadAppPtr;
}

#endif //IT_DATA_DEF_H
