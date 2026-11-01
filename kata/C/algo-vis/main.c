#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define WINDOW_WIDTH 2100
#define WINDOW_HIGHT 1200

#define CONTAINER_HIGHT (WINDOW_HIGHT * 80 / 100)
#define CONTAINER_WIDTH (WINDOW_WIDTH * 90 / 100)

#define N 500
#define DELAY 0

int array[N];
int tmp_array[N];

void FillArray(int n);
void DrawRectangles(SDL_FRect* rects, SDL_Renderer* renderer, int active);
void QuickSort(SDL_FRect* rects, SDL_Renderer* renderer, int start, int end);
void MergeSort(SDL_FRect* rects, SDL_Renderer* renderer, int start, int end);
void UpdateRectangles(SDL_FRect* rects, int n);

int main() {
    FillArray(N);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
            "Sort Visualizer",
            WINDOW_WIDTH,
            WINDOW_HIGHT,
            SDL_WINDOW_OPENGL
            );

    if (!window) {
        SDL_Log("Could not create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer) {
        SDL_Log("Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_FRect* rects = malloc(sizeof(*rects) * N);
    UpdateRectangles(rects, N);

    bool running = true;
    while(running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_Q) {
                QuickSort(rects, renderer, 0, N - 1);
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_M) {
                MergeSort(rects, renderer, 0, N - 1);
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_R) {
                FillArray(N);
            }
        }
        DrawRectangles(rects, renderer, 0);
    }

    free(rects);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void UpdateRectangles(SDL_FRect* rects, int n) {
    float w = (float)CONTAINER_WIDTH / n;
    float unit = (float)CONTAINER_HIGHT / n;
    for (int i = 0; i < n; i++) {
        rects[i].x = (WINDOW_WIDTH - CONTAINER_WIDTH) / 2.0f + w * i;
        rects[i].h = unit * array[i];
        rects[i].y = WINDOW_HIGHT - 50.0f - rects[i].h;
        rects[i].w = w;
    }
}

void FillArray(int n) {
    for (int i = 0; i < n; i++) {
        array[i] = i + 1;
    }

    for (int i = n - 1; i > 0; i--) {
        int j = SDL_rand(i + 1);
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

void DrawRectangles(SDL_FRect* rects, SDL_Renderer* renderer, int active) {
    UpdateRectangles(rects, N);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < N; i++) {
        if (i == active) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rects[i]);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderRect(renderer, &rects[i]);

            SDL_RenderRect(renderer, &rects[i]);
        } else {
            SDL_SetRenderDrawColor(renderer, 80, 255, 80, 255);
            SDL_RenderFillRect(renderer, &rects[i]);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderRect(renderer, &rects[i]);

            SDL_RenderRect(renderer, &rects[i]);
        }
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(DELAY);
}

void QuickSort(SDL_FRect* rects, SDL_Renderer* renderer, int start, int end) { 
    if (start >= end) return;

    int pivot = array[end];
    int border = start;
    for (int i = start; i < end; i++) {
        DrawRectangles(rects, renderer, i);
        if (array[i] < pivot) {
            int tmp = array[i];
            array[i] = array[border];
            array[border] = tmp;
            border++;
            DrawRectangles(rects, renderer, border - 1);
        }
    }
    int tmp = array[border];
    array[border] = array[end];
    array[end] = tmp;
    DrawRectangles(rects, renderer, end);

    QuickSort(rects, renderer, start, border - 1);
    QuickSort(rects, renderer, border + 1, end);
}

void MergeSort(SDL_FRect* rects, SDL_Renderer* renderer, int start, int end) {
    if (start >= end) return;

    int mid = (start + end) / 2;
    MergeSort(rects, renderer, start, mid);
    MergeSort(rects, renderer, mid + 1, end);

    for (int k = start; k <= end; k++) {
        tmp_array[k] = array[k];
    }

    int i = start;
    int j = mid + 1;
    int k = start;

    while (i <= mid && j <= end) {
        if (tmp_array[i] <= tmp_array[j]) {
            array[k] = tmp_array[i];
            i++;
        } else {
            array[k] = tmp_array[j];
            j++;
        }
        DrawRectangles(rects, renderer, k);
        k++;
    }

    while (i <= mid) {
        array[k] = tmp_array[i];
        i++;
        DrawRectangles(rects, renderer, k);
        k++;
    }

    while (j <= end) {
        array[k] = tmp_array[j];
        j++;
        DrawRectangles(rects, renderer, k);
        k++;
    }
}
