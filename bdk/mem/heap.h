/*
 * Copyright (c) 2018 naehrwert
 * Copyright (c) 2018-2024 CTCaer
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _HEAP_H_
#define _HEAP_H_

#include <utils/types.h>

typedef struct _hnode
{
	int used;
	u32 size;
	struct _hnode *prev;
	struct _hnode *next;
	u32 align[4]; // Align to arch cache line size.
} hnode_t;

typedef struct _heap
{
	void *start;
	hnode_t *first;
	hnode_t *last;
} heap_t;

typedef struct
{
	u32 total;
	u32 used;
	u32 nodes_total;
	u32 nodes_used;
} heap_monitor_t;

void heap_init(void *base);
void heap_set(heap_t *heap);
void *malloc(u32 size);
void *calloc(u32 num, u32 size);
void *zalloc(u32 size);
void free(void *buf);
void heap_monitor(heap_monitor_t *mon, bool print_node_stats);

#endif
