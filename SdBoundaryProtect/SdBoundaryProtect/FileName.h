/*++
*
* Copyright (c) 2015 - 2016  �����������¿Ƽ����޹�˾
*
* Module Name:
*
*		FileName.h
*
* Abstract:
*
*		��
*
* Environment:
*
*		Kernel mode
*
* Version:
*
*		��
*
* Author:
*
*		����
*
* Complete Time:
*
*		��
*
* Modify Record:
*
*		��
*
--*/

#pragma once

#define FILE_NAME_TAG	'MNLF'


typedef ULONG	NAME_TYPE;
typedef PULONG	PNAME_TYPE;

#define TYPE_APP		0x00000001
#define TYPE_SYM		0x00000002
#define TYPE_DEV		0x00000004
#define TYPE_UNKNOW		0x00000007
#define	TYPE_FULL_PATH	0x00000008


typedef struct _VOLUME_NAME_INFO
{
	CKrnlStr		AppName;		// like "C:"
	CKrnlStr		SymName;		// like "\\??\\C:"
	CKrnlStr		DevName;		// like "\\Device\\HarddiskVolume12" consider volumes more than 10

	PFLT_INSTANCE	pFltInstance;
	ULONG			ulSectorSize;
	BOOLEAN			bRemoveable;
	BOOLEAN			bOnlyDevName;

	LIST_ENTRY		List;			// struct EntryPointer
} VOLUME_NAME_INFO, *PVOLUME_NAME_INFO, *LPVOLUME_NAME_INFO;


class CFileName
{
public:
	CFileName();
	~CFileName();

	static CKrnlStr* ms_pSystemRoot;
	static CKrnlStr* ms_pPageFileSys;
	static CKrnlStr* ms_pLogFileSys;
	static CKrnlStr* ms_pWmDb;

	BOOLEAN
		Init();

	BOOLEAN
		Unload();

	BOOLEAN
		Clear();

	static
		BOOLEAN
		ToApp(
		__in	CKrnlStr*		pName,
		__inout CKrnlStr*		pAppName,
		__in	PFLT_INSTANCE	pFltInstance
		);

	static
		BOOLEAN
		ToDev(
		__in		CKrnlStr*		pName,
		__inout		CKrnlStr*		pDevName,
		__in_opt	PFLT_INSTANCE	pFltInstance = NULL
		);

	/*
	* ����˵����
	*		��ȡ�ļ���
	*
	* ������
	*		pData
	*		pFltVol	
	*		pName		�ļ���
	*
	* ����ֵ��
	*		TRUE	�ɹ�
	*		FALSE	ʧ��
	*
	* ��ע��
	*		��
	*
	* ����޸�ʱ�䣺
	*		2015/7/3-16:25
	*/
	static
		BOOLEAN
		GetFileFullPath(
		__in	PFLT_CALLBACK_DATA		pData,
		__in	PFLT_VOLUME				pFltVol,
		__out	CKrnlStr			*	pName
		);

	/*
	* ����˵����
	*		��ø�·��
	*
	* ������
	*		pPath			�ļ�·��
	*		pParentPath		�ļ���·��
	*
	* ����ֵ��
	*		TRUE	�ɹ�
	*		FALSE	ʧ��
	*
	* ��ע��
	*		��
	*
	* ����޸�ʱ�䣺
	*		2015/7/3-16:25
	*/
	static
		BOOLEAN
		GetParentPath(
		__in	CKrnlStr * pPath,
		__out	CKrnlStr * pParentPath
		);

	/*
	* ����˵����
	*		��PFLT_VOLUME�л�ȡ�����豸��
	*
	* ������
	*		pFltVol
	*		pName		�����豸��
	*
	* ����ֵ��
	*		TRUE	�ɹ�
	*		FALSE	ʧ��
	*
	* ��ע��
	*		��
	*
	* ����޸�ʱ�䣺
	*		2015/7/3-16:29
	*/
	static
		BOOLEAN
		GetVolDevNameFromFltVol(
		__in	PFLT_VOLUME		pFltVol,
		__out	CKrnlStr	*	pName
		);

	BOOLEAN
		InsertVolNameInfo(
		__in		CKrnlStr*		pAppName,
		__in		CKrnlStr*		pSymName,
		__in		CKrnlStr*		pDevName,
		__in		BOOLEAN			bOnlyDevName,
		__in		BOOLEAN			bRemoveable,
		__in_opt	PFLT_INSTANCE	pFltInstance	= NULL,
		__in		ULONG			ulSectorSize	= 0,
		__in_opt	PBOOLEAN		pbModify		= NULL,
		__in_opt	CKrnlStr*		pOldDevName		= NULL
		);

	BOOLEAN
		DelVolNameInfo(
		__in CKrnlStr* pDevName
		);

	static
		BOOLEAN
		SpliceFilePath(
		__in	CKrnlStr*	pDirPath,
		__in	CKrnlStr*	pFileName,
		__inout	CKrnlStr*	pFilePath
		);

	static
		BOOLEAN
		EqualPureFileName(
		__in CKrnlStr* pFileName1,
		__in CKrnlStr* pFileName2
		);

	static
		BOOLEAN
		GetPureFileName(
		__in CKrnlStr* pFileName,
		__in CKrnlStr* pPureName
		);

	static
		BOOLEAN
		GetExt(
		__in CKrnlStr* pFileName,
		__in CKrnlStr* pExt
		);

	LPVOLUME_NAME_INFO
		GetVolNameInfo(
		__in CKrnlStr*	pName,
		__in NAME_TYPE	NameType
		);

	/*
	* ����˵����
	*		�ж϶����Ƿ��Ǿ�
	*
	* ������
	*		pData
	*		pFileName	������
	*
	* ����ֵ��
	*		TRUE	�Ǿ�
	*		FALSE	���Ǿ�
	*
	* ��ע��
	*		��
	*/
	BOOLEAN
		IsVolume(
		__in PFLT_CALLBACK_DATA		pData,
		__in CKrnlStr			*	pFileName
		);

	/*
	* ����˵����
	*		�����ļ������ȡ�ļ�·��
	*
	* ������
	*		pData
	*		hFile		�ļ����
	*		pFileName	�ļ�·��
	*
	* ����ֵ��
	*		TRUE	�ɹ�
	*		FALSE	ʧ��
	*
	* ��ע��
	*		��
	*/
	static
		BOOLEAN
		GetPathByHandle(
		__in	PFLT_CALLBACK_DATA		pData,
		__in	PCFLT_RELATED_OBJECTS	pFltObjects,
		__in	HANDLE					hFile,
		__out	CKrnlStr			*	pFileName
		);

	static
		BOOLEAN
		IsExpression(
		__in CKrnlStr* pFileName
		);

	static
		BOOLEAN
		ParseAppOrSymName(
		__in	CKrnlStr*	pName,
		__inout CKrnlStr*	pVolName,
		__inout CKrnlStr*	pPartName,
		__inout PBOOLEAN	pbDisk,
		__inout PNAME_TYPE	pNameType
		);

	static
		BOOLEAN
		ParseDevName(
		__in	PFLT_VOLUME	pFltVol,
		__in	CKrnlStr*	pDevName,
		__inout CKrnlStr*	pVolName,
		__inout CKrnlStr*	pPartName
		);

	static
		BOOLEAN
		IsPageFileSys(
		__in CKrnlStr* pFileName
		);

	static
		BOOLEAN
		IsWmDb(
		__in CKrnlStr* pFileName
		);

	static
		BOOLEAN
		SetWmDb(
		__in CKrnlStr* pFileName
		);

	BOOLEAN
		IsDisMountStandard(
		__in		CKrnlStr*		pVolDevName,
		__in		PFLT_INSTANCE	pFltInstance,
		__in_opt	CKrnlStr*		pVolAppName	= NULL
		);

	static
		BOOLEAN
		GetVolAppNameByQueryObj(
		__in	CKrnlStr*	pName,
		__inout CKrnlStr*	pAppName,
		__inout PUSHORT		pusCutOffset
		);

	BOOLEAN
		ParseDevNameFromList(
		__in		CKrnlStr*		pDevName,
		__inout		CKrnlStr*		pVolName,
		__inout		CKrnlStr*		pPartName,
		__out_opt	PFLT_INSTANCE*	pPFltInstance = NULL
		);

	BOOLEAN
		GetFltInstance(
		__in	CKrnlStr*		pFileName,
		__out	PFLT_INSTANCE*	pPFltInstance,
		__in	NAME_TYPE		NameType = TYPE_DEV
		);

	BOOLEAN
		GetSectorSize(
		__in	CKrnlStr*	pFileName,
		__inout ULONG*		pUlSectorSize
		);

	/*
	* ����˵����
	*		�ж��Ƿ���\\Device\\HarddiskVolumeShadowCopy��
	*
	* ������
	*		pFileName	����
	*
	* ����ֵ��
	*		TRUE	��
	*		FALSE	����
	*
	* ��ע��
	*		��
	*/
	BOOLEAN
		IsShadowCopy(
		__in CKrnlStr * pFileName
		);

	/*
	* ����˵����
	*		�ж��Ƿ��ǿ��ƶ��洢����
	*
	* ������
	*		pFileName	�ļ���
	*
	* ����ֵ��
	*		TRUE	��
	*		FALSE	����
	*
	* ��ע��
	*		��
	*/
	BOOLEAN
		IsRemoveable(
		__in CKrnlStr * pFileName
		);

private:
	static LIST_ENTRY	ms_ListHead;	
	static ERESOURCE	ms_Lock;
	static KSPIN_LOCK	ms_SpLock;

	KIRQL				m_Irql;
	LONG				m_LockRef;

	VOID 
		GetLock();

	VOID 
		FreeLock();

	/*
	* ����˵����
	*		��PFLT_CALLBACK_DATA��PFLT_VOLUME�н��ļ���ƴ�ӳ���
	*
	* ������
	*		pData
	*		pFltVol	
	*		pName		�ļ���	
	*
	* ����ֵ��
	*		TRUE	�ɹ�
	*		FALSE	ʧ��
	*
	* ��ע��
	*		��
	*
	* ����޸�ʱ�䣺
	*		2015/7/3-16:27
	*/
	static
		BOOLEAN
		GetFileFullPathFromDataAndFltVol(
		__in	PFLT_CALLBACK_DATA		pData,
		__in	PFLT_VOLUME				pFltVol,
		__out	CKrnlStr			*	pName
		);

	LPVOLUME_NAME_INFO
		GetVolNameInfoByVolAppName(
		__in CKrnlStr* pName
		);

	LPVOLUME_NAME_INFO
		GetVolNameInfoByVolSymName(
		__in CKrnlStr* pName
		);

	LPVOLUME_NAME_INFO
		GetVolNameInfoByVolDevName(
		__in CKrnlStr* pName
		);

	/*
	* ����˵����
	*		��þ����豸��
	*
	* ������
	*		pName		���ķ���������
	*		pDevName	�����豸��
	*
	* ����ֵ��
	*		TRUE	�ɹ�
	*		FALSE	ʧ��
	*
	* ��ע��
	*		��
	*/
	static
		BOOLEAN
		GetVolDevNameByQueryObj(
		__in	CKrnlStr * pName,
		__out	CKrnlStr * pDevName
		);

	BOOLEAN
		IsSystemRootPath(
		__in CKrnlStr* pFileName
		);

	BOOLEAN
		SystemRootToDev(
		__in	CKrnlStr* pFileName,
		__inout CKrnlStr* pFileNameDev
		);

	BOOLEAN
		ConvertByZwQuerySymbolicLinkObject(
		__in	CKrnlStr* pFileName,
		__inout CKrnlStr* pNewFileName
		);
};