/*
 *	PROGRAM:	Client/Server Common Code
 *	MODULE:		dir_list.h
 *	DESCRIPTION:	Directory listing config file operation
 *
 * The contents of this file are subject to the Interbase Public
 * License Version 1.0 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy
 * of the License at http://www.Inprise.com/IPL.html
 *
 * Software distributed under the License is distributed on an
 * "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express
 * or implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * Created by: Alex Peshkov <AlexPeshkov@users.sourceforge.net>
 *
 * All Rights Reserved.
 * Contributor(s): ______________________________________.
 */

#ifndef _DIR_LIST_H_
#define _DIR_LIST_H_

//
// This class is used internally by DirectoryList
// to store single path in format of pre-parsed
// elements of that path & perform basic operations
// with this path representation.
// Because of it's internal nature it has only
// internally required subset of possible operators.
//
class ParsedPath {
	Firebird::string * PathElem;
	int nElem;
	Firebird::string SubPath(int n) const;
public:
	ParsedPath(void);
	ParsedPath(const Firebird::string & path);
	~ParsedPath();
	// Take new path inside
	void Parse(const Firebird::string & path);
	// Convert internal representation to traditional one
	operator Firebird::string();
	// Compare with path given by constant
	bool operator==(const char * path);
	// Check, whether pPath lies inside directory tree,
	// specified by *this ParsedPath. Also checks against
	// possible symbolic links.
	bool Contains(const ParsedPath & pPath);
};

class DirectoryList {
private:
	ParsedPath * ConfigDirs;
	int nDirs;
	// Initialize loads data from Config Manager.
	// With simple mutex add-on may be easily used to 
	// load them dynamically. Now called locally
	// when IsPathInList() invoked first time.
	void Initialize(void);
protected:
	// Used for various configuration parameters - 
	// returns parameter string from Config Manager.
	virtual const Firebird::string GetConfigString(void) = 0;
public:
	DirectoryList();
	~DirectoryList();
	// Check, whether Path inside this DirectoryList
	bool IsPathInList(const Firebird::string & Path);
};
#endif //	_DIR_LIST_H_	
