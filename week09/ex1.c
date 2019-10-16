#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool char
#define true 1
#define false 0

#define PAGEPOOL_SIZE 4096

typedef struct {
    int id;
    // Dedicate a 8bit number for age counter
    char age;
    bool R;

} Page;

// Create fixed pool of 4096 pages
Page pagepool[PAGEPOOL_SIZE];

void run(int page_frames, char *input) {
    Page *pages = calloc(page_frames, sizeof(Page));
    int loaded_pages = 0;
    int hits = 0;
    int misses = 0;
    int tickCounter = 0;

    char *token = strtok(input, " ");
    do {
        int id;
        sscanf(token, "%d", &id);
        //printf("%d\n", id);

        // Since we don't use real RAM, using timer for aging tick is useless,
        // even the first tick would happens long after all memory accesses
        // are passed. So, we will trigger a tick after some fixed amount of
        // access operations.
        if (tickCounter == 50) {
            // Update pages information
            for (int i = 0; i < loaded_pages; i++) {
                Page *p = &pages[i];

                // Shift the counter right by 1 bit
                p->age >>= 1;
                // Set the leftmost bit to the R (0 or 1)
                p->age |= (p->R << 7);
                // Erase R flag on the page
                p->R = 0;
            }

            // Erase the tick counter, so we can go into this state once again
            tickCounter = 0;
        }

        // Perform memory access operation
        // Search for the most optimal page to replace and for the required
        // page at the same timer
        int most_optimal_page = 0;
        int most_optimal_age = 0xFF;
        bool success = false;
        for (int i = 0; i < loaded_pages; i++) {
            Page *page = &pages[i];
            if (page->id == id) {
                hits++;
                page->R = 1;
                //printf("Found a page at %d\n", i);
                success = true;
                break;
            }

            if (page->age < most_optimal_age) {
                most_optimal_page = i;
                most_optimal_age = page->age;
            }
        }

        // The required page is not loaded, load it
        if (!success) {
            misses++;

            if (loaded_pages < page_frames) {
                //printf("Miss occurred, adding new page\n");
                pages[loaded_pages++] = pagepool[id];
            } else {
                //printf("Miss occurred, replacing page %d\n", most_optimal_page);

                // Write back the page we are going to swap out
                pagepool[pages[most_optimal_page].id] = pages[most_optimal_page];
                // Swap in the new page
                pages[most_optimal_page] = pagepool[id];
            }
        }

        token = strtok(0, " ");
    } while (token);

    printf("Completed. %d hits, %d misses; hit/miss ratio: %f\n", hits, misses, (float) hits/misses);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage:\n\
ex1 <page frames count> <read order file>\n");
        return 1;
    }

    // Initialize all pages in the pool
    for (int i = 0; i < PAGEPOOL_SIZE; i++) {
        Page page;
        page.id = i;
        page.age = 0;
        page.R = 0;
        pagepool[i] = page;
    }

    int page_frames;
    char filename[1024];

    sscanf(argv[1], "%d", &page_frames);
    sscanf(argv[2], "%s", filename);

    printf("Running page system simulation with %d page frames\n", page_frames);
    printf("File with page access order: \"%s\"\n", filename);

    // Open the file
    FILE *file = fopen(filename, "r");
    // Get the file size using seek() and get back to the beginning
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Create a buffer for the string (+1 character for \0)
    char *file_str = malloc(file_size + 1);
    // Read file_size chars from the file and store them to the file_str
    fread(file_str, 1, file_size, file);

    // Run the simulation
    run(page_frames, file_str);

    return 0;
}
