/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "DirectoryNodeStudio.h"
#include "QueryParams.h"
#include "video/VideoDatabase.h"

using namespace XFILE::VIDEODATABASEDIRECTORY;

CDirectoryNodeStudio::CDirectoryNodeStudio(const CStdString& strName, CDirectoryNode* pParent)
  : CDirectoryNode(NODE_TYPE_STUDIO, strName, pParent)
{

}

NODE_TYPE CDirectoryNodeStudio::GetChildType() const
{
  CQueryParams params;
  CollectQueryParams(params);
  if (params.GetContentType() == VIDEODB_CONTENT_MOVIES)
    return NODE_TYPE_TITLE_MOVIES;
  if (params.GetContentType() == VIDEODB_CONTENT_MUSICVIDEOS)
    return NODE_TYPE_TITLE_MUSICVIDEOS;

  return NODE_TYPE_TITLE_TVSHOWS;
}

CStdString CDirectoryNodeStudio::GetLocalizedName() const
{
  CVideoDatabase db;
  if (db.Open())
    return db.GetStudioById(GetID());
  return "";
}

bool CDirectoryNodeStudio::GetContent(CFileItemList& items) const
{
  CVideoDatabase videodatabase;
  if (!videodatabase.Open())
    return false;

  CQueryParams params;
  CollectQueryParams(params);

  bool bSuccess=videodatabase.GetStudiosNav(BuildPath(), items, params.GetContentType());

  videodatabase.Close();

  return bSuccess;
}
