/*
**
**
**  Copyright (C) 2014 Cisco and/or its affiliates. All rights reserved.
**  Copyright (C) 2012-2013 Sourcefire, Inc.
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License Version 2 as
**  published by the Free Software Foundation.  You may not use, modify or
**  distribute this program under any other version of the GNU General
**  Public License.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**
**  Author(s):  Hui Cao <hcao@sourcefire.com>
**
**  NOTES
**  5.25.2012 - Initial Source Code. Hcao
*/
#ifndef __FILE_CONFIG_H__
#define __FILE_CONFIG_H__
#include "file_lib.h"
#include "file_identifier.h"

#define FILE_ID_MAX          1024

typedef struct _IdentifierMemoryBlock
{
    void *mem_block;  /*the node that is shared*/
    struct _IdentifierMemoryBlock *next;  /*next node*/
}IdentifierMemoryBlock;

typedef struct _fileConfig
{
    IdentifierNode *identifier_root; /*Root of magic tries*/
    IdentifierMemoryBlock *id_memory_root; /*root of memory used*/
    RuleInfo *FileRules[FILE_ID_MAX + 1];
    int64_t file_type_depth;
    int64_t file_signature_depth;
    int64_t file_block_timeout;
    int64_t file_lookup_timeout;
    bool block_timeout_lookup;
    int64_t file_capture_memcap;
    int64_t file_capture_max_size;
    int64_t file_capture_min_size;
    int64_t file_capture_block_size;
#if defined(DEBUG_MSGS) || defined (REG_TEST)
    int64_t show_data_depth;
#endif
    int64_t file_depth;
} FileConfig;


#if defined(FEAT_FILE_INSPECT)
/* Return all rule id's that match a a given "type" string.  */
bool get_ids_from_type( const void * conf, const char * type, uint32_t ** ids, int * count );

/* Return all rule id's that match a a given "type" and "version" strings.  */
bool get_ids_from_type_version( const void * conf, const char * type, const char * version,
        uint32_t ** ids, int * count );

/* Return all rule id's in a given file rule group. */
bool get_ids_from_group( const void * conf, const char * group, uint32_t ** ids, int * count );
#endif /* FEAT_FILE_INSPECT */

/*
 * Parse file magic rule
 *
 * Args:
 *   char *args: file magic rule string
 *   void *file_config: pointer to file config
 */
void file_rule_parse(char *args, void *file_config);

/*
 * Get rule information
 *
 * Args:
 *   void *file_config: pointer to file config
 *   uint32_t rule_id: file rule ID
 */
RuleInfo *file_rule_get(void *conf, uint32_t rule_id);

/* Free resource used by file rules
 *
 * Args:
 *   void *file_config: pointer to file config
 */
void file_rule_free(void* conf);
#endif

