/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Blake Ross <blakeross@telocity.com>
 *   Ben Goodger <ben@netscape.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or 
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
 
#ifndef downloadmanager___h___
#define downloadmanager___h___
#include "nsIDownloadManager.h"
#include "nsIRDFDataSource.h"
#include "nsIRDFRemoteDataSource.h"
#include "nsIRDFContainer.h"
#include "nsIRDFService.h"
#include "nsIRDFContainerUtils.h"
#include "nsIObserver.h"
#include "nsIWebProgressListener.h"
#include "nsIWebBrowserPersist.h"
#include "nsIRequestObserver.h"
#include "nsIURI.h"
#include "nsILocalFile.h"
 
class nsDownloadManager : public nsIDownloadManager,
                          public nsIRDFDataSource
{
public:
  NS_DECL_NSIRDFDATASOURCE
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOWNLOADMANAGER

  nsresult Init();

  nsDownloadManager();
  virtual ~nsDownloadManager();

protected:
  nsresult GetDownloadsContainer(nsIRDFContainer** aResult);
  nsresult GetProfileDownloadsFileURL(char** aDownloadsFileURL);


protected:
  nsCOMPtr<nsIRDFDataSource> mInner;
  nsCOMPtr<nsISupportsArray> mObservers;
  nsCOMPtr<nsIRDFService> mRDFService;
  nsCOMPtr<nsIRDFContainerUtils> mRDFContainerUtils;

};


 
class DownloadItem : public nsIWebProgressListener
{
public:
  NS_DECL_NSIWEBPROGRESSLISTENER
  DownloadItem();
  virtual ~DownloadItem();

  nsresult Init(nsIRDFResource* aDownloadItem, 
                nsIRDFDataSource* aDataSource,
                nsIURI* aURI, nsIInputStream* aPostData, nsILocalFile* aFile);

protected:
  nsresult UpdateProgressInfo();

protected:
  nsCOMPtr<nsIWebBrowserPersist> mWebBrowserPersist;
  nsCOMPtr<nsIRequestObserver> mRequestObserver;
  nsIRDFResource* mDownloadItem;
  nsIRDFDataSource* mDataSource;

  PRInt32 mCurTotalProgress;
  PRInt32 mMaxTotalProgress;
};
#endif