/*
 * Copyright (C) 2017 ARM Ltd.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>

#define PAGE_SIZE		sysconf(_SC_PAGESIZE)
#define PAGE_PRESENT_MASK	(1ULL<<63)
#define PAGE_PFN_MASK		((1ULL<<55) - 1)

volatile char *victim_area;

unsigned long virt_to_phys(unsigned long virt)
{
	FILE *pagemap;
	uint64_t record;
	unsigned long pfn;
	int record_off = (virt / PAGE_SIZE) * sizeof(record);

	if (!(pagemap = fopen("/proc/self/pagemap", "r")))
		exit(1);

	if (lseek(fileno(pagemap), record_off, SEEK_SET) != record_off)
		exit(1);

	if (!fread(&record, sizeof(record), 1, pagemap))
		exit(1);
	fclose(pagemap);

	if (!(record & PAGE_PRESENT_MASK))
		exit(1);

	pfn = record & PAGE_PFN_MASK;
	return (pfn * PAGE_SIZE) | (virt & (PAGE_SIZE - 1));
}

int main(int argv, char **argc)
{
	int i;
	unsigned long sum;

	if (geteuid()) {
		fprintf(stderr, "This program needs to be run as root\n");
		exit(1);
	}

	victim_area = calloc(1, PAGE_SIZE);
	if (!victim_area) {
		fprintf(stderr, "Failed to allocate memory\n");
		exit(1);
	}

	memset((void *)victim_area, '>', PAGE_SIZE);

	fprintf(stderr, "Buffer Physical address: 0x%lx\n",
		virt_to_phys((unsigned long)victim_area));

	/* Do nothing */
	while (1) {
		sum = 0;
		for (i = 0; i < PAGE_SIZE; i++)
		{
			sum += victim_area[i];
		}
	}

	return 0;
}
