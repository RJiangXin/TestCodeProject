// Copyright (C) RenZhai.2020.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "HTTP/Core/SimpleHTTPHandle.h"
#include "SimpleHTTPType.h"
#ifdef PLATFORM_PROJECT
#include "Tickable.h"
#endif

class FSimpleHttpActionRequest;
const FName NONE_NAME = TEXT("NONE");
/*
 * A simple set of HTTP interface functions can quickly perform HTTP code operations. 
 * Only one interface is needed to interact with our HTTP server. Currently, 
 * HTTP supports downloading, uploading, deleting and other operations. 
 * See our API for details
*/
class SIMPLEHTTP_API FSimpleHttpManage 
#ifdef PLATFORM_PROJECT
	:public FTickableGameObject
#endif
{
	/**
	 * Used to determine whether the object should be ticked in the editor.  Defaults to false since
	 * that is the previous behavior.
	 *
	 * @return	true if this tickable object can be ticked in the editor
	 */
	virtual bool IsTickableInEditor() const;

	/** return the stat id to use for this tickable **/
	virtual TStatId GetStatId() const;

	/** Get HTTP function collection  **/
	struct SIMPLEHTTP_API FHTTP
	{
		/*We want to have direct access to the commands in http .*/
		friend class FSimpleHttpManage;

		FHTTP();

		 /**
		  * Pause all downloading content.
		*/
		void Suspend();

		/**
		 * awaken all downloading Pause content.
		*/
		void Awaken();

		/**
		 * Specify the content to pause the download.
		 */
		bool Suspend(const FSimpleHTTPHandle& Handle);
		
		/**
		 * Cancel all downloads.
		 */
		bool Cancel();
	
		/**
		 * 	Cancel the specified Download.
		*/
		bool Cancel(const FSimpleHTTPHandle& Handle);

		/*Gets the handle of the last execution request*/
		FSimpleHTTPHandle GetHandleByLastExecutionRequest();

		/**
		 * Submit form to server.
		 *
		 * @param InURL						Address to visit.
		 * @param InParam					Parameters passed.
		 * @param BPResponseDelegate		Proxy for site return.
		 */
		bool PostRequest(const TCHAR *InURL, const TCHAR *InParam, const FSimpleHttpBpResponseDelegate &BPResponseDelegate);

		/**
		 * The data can be downloaded to local memory via the HTTP serverll .
		 *
		 * @param BPResponseDelegate	Proxy set relative to the blueprint.
		 * @param URL					domain name .
		 * @Return						Returns true if the request succeeds 
		 */
		bool GetObjectToMemory(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL);
		
		/**
		 * The data can be downloaded to local memory via the HTTP serverll.
		 * Can download multiple at one time .
		 *
		 * @param BPResponseDelegate	Proxy set relative to the blueprint.
		 * @param URL					Need domain name .
		 */
		void GetObjectsToMemory(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const TArray<FString> &URL);

		/**
		 * Download individual data locally.
		 *
		 * @param BPResponseDelegate	Proxy set relative to the blueprint.
		 * @param URL					domain name .
		 * @param SavePaths				Path to local storage .
		 * @Return						Returns true if the request succeeds 
		 */
		bool GetObjectToLocal(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL, const FString &SavePaths);
		
		/**
		 * Download multiple data to local .
		 *
		 * @param BPResponseDelegate	Proxy set relative to the blueprint.
		 * @param URL					Need domain name .
		 * @param SavePaths				Path to local storage .
		 */
		void GetObjectsToLocal(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const TArray<FString> &URL, const FString &SavePaths);

		/**
		 * Upload single file from disk to server .
		 *
		 * @param BPResponseDelegate	Proxy set relative to the blueprint.
		 * @param URL					domain name .
		 * @param LocalPaths			Specify the Path where you want to upload the file.
		 * @Return						Returns true if the request succeeds
		 */
		bool PutObjectFromLocal(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL, const FString &LocalPaths);
		
		/**
		 * Upload duo files from disk to server  .
		 *
		 * @param BPResponseDelegate	Proxy set relative to the blueprint.
		 * @param URL					domain name .
		 * @param LocalPaths			Specify the Path where you want to upload the file.
		 * @Return						Returns true if the request succeeds
		 */
		bool PutObjectsFromLocal(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL, const FString &LocalPaths);

		/**
		 * Can upload byte data .
		 *
		 * @param BPResponseDelegate	Proxy set relative to the blueprint.
		 * @param URL					domain name .
		 * @param Buffer				Byte code data.
		 * @Return						Returns true if the request succeeds
		 */
		bool PutObjectFromBuffer(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL, const TArray<uint8> &Buffer);
		
		/**
		 * Can upload string data .
		 *
		 * @param BPResponseDelegate	Proxy set relative to the blueprint.
		 * @param URL					domain name .
		 * @param Buffer				string code data.
		 * @Return						Returns true if the request succeeds
		 */
		bool PutObjectFromString(const FSimpleHttpBpResponseDelegate& BPResponseDelegate, const FString& URL, const FString& InBuffer);

		/**
		 * Stream data upload supported by UE4 .
		 *
		 * @param BPResponseDelegate	Proxy set relative to the blueprint.
		 * @param URL					domain name .
		 * @param Stream				UE4 storage structure .
		 * @Return						Returns true if the request succeeds
		 */
		bool PutObjectFromStream(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL, TSharedRef<FArchive, ESPMode::ThreadSafe> Stream);

		/**
		 * Remove a single object from the server .
		 *
		 * @param BPResponseDelegate	Proxy set relative to the blueprint.
		 * @param URL					domain name .
		 * @Return						Returns true if the request succeeds
		 */
		bool DeleteObject(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const FString &URL);
		
		/**
		 * Multiple URLs need to be specified to remove multiple objects from the server .
		 *
		 * @param BPResponseDelegate	Proxy set relative to the blueprint.
		 * @param URL					Need domain name .
		 */
		void DeleteObjects(const FSimpleHttpBpResponseDelegate &BPResponseDelegate, const TArray<FString> &URL);
		
		//////////////////////////////////////////////////////////////////////////

		/**
		 * Submit form to server.
		 *
		 * @param InURL						Address to visit.
		 * @param InParam					Parameters passed.
		 * @param BPResponseDelegate		Proxy for site return.
		 */
		bool PostRequest(const TCHAR *InURL, const TCHAR *InParam, const FSimpleHttpResponseDelegate &BPResponseDelegate);

		/**
		 * The data can be downloaded to local memory via the HTTP serverll .
		 *
		 * @param BPResponseDelegate	C + + based proxy interface .
		 * @param URL					domain name .
		 * @Return						Returns true if the request succeeds
		 */
		bool GetObjectToMemory(const FSimpleHttpResponseDelegate &BPResponseDelegate, const FString &URL);

		/**
		 * The data can be downloaded to local memory via the HTTP serverll.
		 * Can download multiple at one time .
		 *
		 * @param BPResponseDelegate	C + + based proxy interface .
		 * @param URL					Need domain name .
		 */
		void GetObjectsToMemory(const FSimpleHttpResponseDelegate &BPResponseDelegate, const TArray<FString> &URL);

		/**
		 * Download individual data locally.
		 *
		 * @param BPResponseDelegate	C + + based proxy interface .
		 * @param URL					domain name .
		 * @param SavePaths				Path to local storage .
		 * @Return						Returns true if the request succeeds
		 */
		bool GetObjectToLocal(const FSimpleHttpResponseDelegate &BPResponseDelegate, const FString &URL, const FString &SavePaths);

		/**
		 * Download multiple data to local .
		 *
		 * @param BPResponseDelegate	C + + based proxy interface .
		 * @param URL					Need domain name .
		 * @param SavePaths				Path to local storage .
		 */
		void GetObjectsToLocal(const FSimpleHttpResponseDelegate &BPResponseDelegate, const TArray<FString> &URL, const FString &SavePaths);

		/**
		 * Upload single file from disk to server .
		 *
		 * @param BPResponseDelegate	C + + based proxy interface .
		 * @param URL					domain name .
		 * @param LocalPaths			Specify the Path where you want to upload the file.
		 * @Return						Returns true if the request succeeds
		 */
		bool PutObjectFromLocal(const FSimpleHttpResponseDelegate &BPResponseDelegate, const FString &URL, const FString &LocalPaths);

		/**
		 * Upload duo files from disk to server  .
		 *
		 * @param BPResponseDelegate	C + + based proxy interface .
		 * @param URL					domain name .
		 * @param LocalPaths			Specify the Path where you want to upload the file.
		 * @Return						Returns true if the request succeeds
		 */
		bool PutObjectsFromLocal(const FSimpleHttpResponseDelegate &BPResponseDelegate, const FString &URL, const FString &LocalPaths);

		/**
		 * Can upload byte data .
		 *
		 * @param BPResponseDelegate	C + + based proxy interface .
		 * @param URL					domain name .
		 * @param Buffer				Byte code data.
		 * @Return						Returns true if the request succeeds
		 */
		bool PutObjectFromBuffer(const FSimpleHttpResponseDelegate &BPResponseDelegate, const FString &URL, const TArray<uint8> &Buffer);
		
		/**
		 * Can upload string data .
		 *
		 * @param BPResponseDelegate	Proxy set relative to the blueprint.
		 * @param URL					domain name .
		 * @param Buffer				string code data.
		 * @Return						Returns true if the request succeeds
		 */
		bool PutObjectFromString(const FSimpleHttpResponseDelegate& BPResponseDelegate, const FString& URL, const FString& InBuffer);

		/**
		 * Stream data upload supported by UE4 .
		 *
		 * @param BPResponseDelegate	C + + based proxy interface .
		 * @param URL					domain name .
		 * @param Stream				UE4 storage structure .
		 * @Return						Returns true if the request succeeds
		 */
		bool PutObjectFromStream(const FSimpleHttpResponseDelegate &BPResponseDelegate, const FString &URL, TSharedRef<FArchive, ESPMode::ThreadSafe> Stream);

		/**
		 * Remove a single object from the server .
		 *
		 * @param BPResponseDelegate	C + + based proxy interface .
		 * @param URL					domain name .
		 * @Return						Returns true if the request succeeds
		 */
		bool DeleteObject(const FSimpleHttpResponseDelegate &BPResponseDelegate, const FString &URL);

		/**
		 * Multiple URLs need to be specified to remove multiple objects from the server .
		 *
		 * @param BPResponseDelegate	C + + based proxy interface .
		 * @param URL					Need domain name .
		 */
		void DeleteObjects(const FSimpleHttpResponseDelegate &BPResponseDelegate, const TArray<FString> &URL);

	private:

		/**
		 * Register our agent BP for internal use .
		 *
		 * @param return	Use handle find PRequest.
		 */
		FSimpleHTTPHandle RegisteredHttpRequest(EHTTPRequestType RequestType = EHTTPRequestType::SINGLE,
			FSimpleHttpSingleRequestCompleteDelegate SimpleHttpRequestCompleteDelegate = FSimpleHttpSingleRequestCompleteDelegate(),
			FSimpleHttpSingleRequestProgressDelegate	SimpleHttpRequestProgressDelegate = FSimpleHttpSingleRequestProgressDelegate(),
			FSimpleHttpSingleRequestHeaderReceivedDelegate SimpleHttpRequestHeaderReceivedDelegate = FSimpleHttpSingleRequestHeaderReceivedDelegate(), 
			FAllRequestCompleteDelegate AllRequestCompleteDelegate = FAllRequestCompleteDelegate());

		/**
		 * Register our agent BP for internal use .
		 *
		 * @param return	Use handle find PRequest.
		 */
		FSimpleHTTPHandle RegisteredHttpRequest(EHTTPRequestType RequestType = EHTTPRequestType::SINGLE,
			FSimpleSingleCompleteDelegate SimpleHttpRequestCompleteDelegate = nullptr,
			FSimpleSingleRequestProgressDelegate	SimpleHttpRequestProgressDelegate = nullptr,
			FSimpleSingleRequestHeaderReceivedDelegate SimpleHttpRequestHeaderReceivedDelegate = nullptr,
			FSimpleDelegate AllRequestCompleteDelegate = nullptr);

		/** 
		 * Refer to the previous API for internal use details only 
		 *
		 * @param Handle	Easy to find requests .
		 */
		bool GetObjectToMemory(const FSimpleHTTPHandle &Handle,const FString &URL);
		
		/** 
		 * Refer to the previous API for internal use details only 
		 *
		 * @param Handle	Easy to find requests .
		 */
		void GetObjectsToMemory(const FSimpleHTTPHandle &Handle, const TArray<FString> &URL);
	
		/**
		 * Refer to the previous API for internal use details only
		 *
		 * @param Handle	Easy to find requests .
		 */
		bool GetObjectToLocal(const FSimpleHTTPHandle &Handle, const FString &URL, const FString &SavePaths);

		/**
		 * Refer to the previous API for internal use details only
		 *
		 * @param Handle	Easy to find requests .
		 */
		void GetObjectsToLocal(const FSimpleHTTPHandle &Handle, const TArray<FString> &URL, const FString &SavePaths);
	
		/**
		 * Refer to the previous API for internal use details only
		 *
		 * @param Handle	Easy to find requests .
		 */
		bool PutObjectFromLocal(const FSimpleHTTPHandle &Handle, const FString &URL, const FString &LocalPaths);
		
		/**
		 * Refer to the previous API for internal use details only
		 *
		 * @param Handle	Easy to find requests .
		 */
		bool PutObjectsFromLocal(const FSimpleHTTPHandle &Handle, const FString &URL, const FString &LocalPaths);
		
		/**
		 * Refer to the previous API for internal use details only
		 *
		 * @param Handle	Easy to find requests .
		 */
		bool PutObjectFromBuffer(const FSimpleHTTPHandle &Handle, const FString &URL, const TArray<uint8> &Buffer);
		
		/**
		 * Refer to the previous API for internal use details only
		 *
		 * @param Handle	Easy to find requests .
		 */
		bool PutObjectFromString(const FSimpleHTTPHandle& Handle, const FString& URL, const FString& Buffer);

		/**
		 * Refer to the previous API for internal use details only
		 *
		 * @param Handle	Easy to find requests .
		 */
		bool PutObjectFromStream(const FSimpleHTTPHandle &Handle, const FString &URL, TSharedRef<FArchive, ESPMode::ThreadSafe> Stream);
	
		/**
		 * Refer to the previous API for internal use details only
		 *
		 * @param Handle	Easy to find requests .
		 */
		bool DeleteObject(const FSimpleHTTPHandle &Handle, const FString &URL);
		
		/**
		 * Refer to the previous API for internal use details only
		 *
		 * @param Handle	Easy to find requests .
		 */
		void DeleteObjects(const FSimpleHTTPHandle &Handle, const TArray<FString> &URL);

		/**
		 * Submit form to server.
		 *
		 * @param Handle					It can be used to retrieve the corresponding request.
		 * @param InURL						Address to visit.
		 */
		bool PostRequest(const FSimpleHTTPHandle &Handle, const FString &URL);

	private:
		/*You can find the corresponding request according to the handle  */
		TWeakPtr<FSimpleHttpActionRequest> Find(const FSimpleHTTPHandle &Handle);

		/*HTTP Map*/
		TMap<FSimpleHTTPHandle, TSharedPtr<FSimpleHttpActionRequest>> HTTPMap;

		/*Pause all download tasks*/
		/*UE HTTP currently does not support single pause. However, we support the suspension of the entire HTTP download!*/
		bool bPause;

		/*The handle points to the request just pointed to*/
		FName TemporaryStorageHandle;
	};

public:
	virtual ~FSimpleHttpManage(){}

	/**
	 * GC
	 * Pure virtual that must be overloaded by the inheriting class. It will
	 * be called from within LevelTick.cpp after ticking all actors or from
	 * the rendering thread (depending on bIsRenderingThreadObject)
	 *
	 * @param DeltaTime	Game time passed since the last call.
	 */
	virtual void Tick(float DeltaTime);

	static FSimpleHttpManage *Get();
	static void Destroy();

	/** Get HTTP function collection  **/
	FORCEINLINE FHTTP &GetHTTP() { return HTTP; }
private:

	static FSimpleHttpManage *Instance;
	FHTTP HTTP;
	FCriticalSection Mutex;
};

#define SIMPLE_HTTP FSimpleHttpManage::Get()->GetHTTP()
