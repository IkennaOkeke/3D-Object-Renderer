#include <stdio.h>
#include <stdlib.h>
#include "spheres.h"
#include "vector.h"
#include "color.h"

// Global variable declaration
Vec3 CAMERA_POSITION = {(float)0.00, (float)0.00, (float)0.00};
Vec3 CAMERA_DIRECTION;

int IMAGE_WIDTH, IMAGE_HEIGHT;

float VIEWPORT_WIDTH, VIEWPORT_HEIGHT, VIEWPORT_Z;

float FOCAL_LENGTH;

Vec3 LIGHT_POSITION;
float LIGHT_BRIGHTNESS;

int COLOUR_NUMBER, BACKGROUND_COLOUR_INDEX;

Vec3 BACKGROUND_COLOUR = {(float)0.00, (float)0.00, (float)0.00}; //default background colour (for milestone 2)

int SPHERE_NUMBER;

float SHADOW_FACTOR = 0.1;

Vec3 SPHERE_COLOUR = {(float)1.00, (float)1.00, (float)1.00};

unsigned int COLOURS;




// main function
int main(int argc, char *argv[]) {

    // obtains input and output files using argc/argv
    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    // operation with argc to prevent errors
    int b = argc;
    b += 1;

    // world class initialization and memory allocation
    World *world = (World *)malloc(sizeof(World));
    worldInit(world);

    // gets the image dimensions
    fscanf(input_file, "%d %d", &IMAGE_WIDTH, &IMAGE_HEIGHT);

    // gets the image viewpoint_height, viewpoint_width (using a simple x/y = a/b calculation), and focal_length
    fscanf(input_file, "%f", &VIEWPORT_HEIGHT);
    fscanf(input_file, "%f", &FOCAL_LENGTH);
    VIEWPORT_Z = -1 * FOCAL_LENGTH;
    VIEWPORT_WIDTH = ((float)IMAGE_WIDTH / IMAGE_HEIGHT) * VIEWPORT_HEIGHT;

    // gets the light position and light brightness
    fscanf(input_file, "%f %f %f %f", &LIGHT_POSITION.x, &LIGHT_POSITION.y, &LIGHT_POSITION.z, &LIGHT_BRIGHTNESS);

    // gets the colours and stores in array
    fscanf(input_file, "%d", &COLOUR_NUMBER);
    unsigned int COLOURS[COLOUR_NUMBER];
    for (int index = 0; index < COLOUR_NUMBER; index++) {

        fscanf(input_file, "%x", &COLOURS[index]);

    }

    // executes a statement using the COLOURS array to prevent errors // remove later
    unsigned int a = COLOURS[0];
    a += 1;

    // gets background colour index
    fscanf(input_file, "%d", &BACKGROUND_COLOUR_INDEX);

    // gets sphere amount, and creates an array of spheres and an array of ints for colour indexes
    fscanf(input_file, "%d", &SPHERE_NUMBER);
    // Sphere SPHERES[SPHERE_NUMBER];
    int SPHERE_COLOUR_INDEXES[SPHERE_NUMBER];

    // for loop to store the info for each sphere; its position and colour
    for (int index = 0; index < SPHERE_NUMBER; index++) {

        //creates empty sphere and adds it to World
        Sphere *empty_sphere = createSphere(0.00, CAMERA_POSITION, SPHERE_COLOUR);
        addSphere(world, empty_sphere);

        fscanf(input_file, "%f %f %f %f %d", &(((world->spheres)[index])->pos.x), &(((world->spheres)[index])->pos.y), &(((world->spheres)[index])->pos.z), &(((world->spheres)[index])->r), &SPHERE_COLOUR_INDEXES[index]);
        (world->spheres)[index]->color = SPHERE_COLOUR;

    }

    // closes input file
    fclose(input_file);



    // prints info needed for ppm file
    fprintf(output_file, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    // variable declaration for upcoming loop/s
    Vec3 current_pixel;
    Vec3 current_sphere_pos;
    float t;
    float width_ratio = VIEWPORT_WIDTH / IMAGE_WIDTH;
    float height_ratio = VIEWPORT_HEIGHT / IMAGE_HEIGHT;

    // for loops to iterate through each pixel
    for (int y_index = (IMAGE_HEIGHT - 1); y_index >= 0; y_index--) {

        for (int x_index = 0; x_index < IMAGE_WIDTH; x_index++) {

            // scales current pixel to viewport dimensions
            current_pixel.x = ((float)x_index - (float)IMAGE_WIDTH / 2.0) * width_ratio + (width_ratio / 2.0);
            current_pixel.y = ((float)y_index - (float)IMAGE_HEIGHT / 2.0) * height_ratio + (height_ratio / 2.0);
            current_pixel.z = (float)VIEWPORT_Z;

            // initializes min_t value. Needed to store t of closest sphere, if any
            float min_t = -1;

            // for loop to iterate through each possible sphere
            for (int index = 0; index < SPHERE_NUMBER; index++) {

                // checks to see if the ray at the current pixel intersects with a sphere
                int intersect_check = doesIntersect(((world->spheres)[index]), CAMERA_POSITION, current_pixel, &t);

                // if not, then the current pixel is not part of a sphere, we can continue
                if (intersect_check == 0) {
                    continue;
                }

                // if the current pixel is part of a sphere, we check to make sure the current pixel shows the frontmost sphere by choosing the lowest t value
                if ((t < min_t) || (min_t == -1)) {
                    min_t = t;
                    current_sphere_pos = ((world->spheres)[index])->pos;
                }

            }

            Vec3 final_colour;

            // sets final colour to the background colour if current pixel is not part of a sphere
            if ((min_t == -1)) {
                final_colour = BACKGROUND_COLOUR;
            }
            // shades sphere accordingly if pixel is a part of a sphere
            else {
                // using our t value and info given by the user, we create vectors/variables needed for our shading calculation 
                Vec3 intersection = scalarMultiply(min_t, current_pixel);;
                Vec3 light_direction = subtract(LIGHT_POSITION, intersection);
                Vec3 s_colour = {(float)1.00, (float)1.00, (float)1.00};
                Vec3 surface_normal = normalize(subtract(intersection, current_sphere_pos));
                Vec3 light_direction_normal = normalize(light_direction);
                float light_dot_surface = dot(light_direction_normal, surface_normal);
                float max = 0;
                if (max < light_dot_surface) {
                    max = light_dot_surface;
                }

                // calculates intensity value
                float dist = distance(LIGHT_POSITION, intersection) * distance(LIGHT_POSITION, intersection);
                float I_0 = LIGHT_BRIGHTNESS * (max/dist);
                float I = 1.0;

                // caps our intensity value
                if (I > I_0) {
                    I = I_0;
                }
                
                // calculates colour using intensity and sphere colour
                final_colour = scalarMultiply(I, s_colour);

                // for loop and variables to check for shading eligibility
                int intersect_check = 0;
                float light_t = -1;
                for (int index = 0; index < SPHERE_NUMBER; index++) {

                    // checks to see if the ray that goes from the current pixel's intersection point (with the sphere) to the light source intersects with another sphere
                    intersect_check = doesIntersect(((world->spheres)[index]), add(intersection, scalarMultiply(0.001, surface_normal)), light_direction_normal, &light_t);

                    // if it doesn't we check the next sphere, but if it does we exit the loop
                    if (intersect_check == 0) {
                        continue;
                    }
                    else {
                        break;
                    }
                }

                // shades in current pixel if necessary
                if (intersect_check == 1) {
                    final_colour = scalarMultiply(SHADOW_FACTOR, final_colour);
                }

            }

            // readjust our color scale to [0-255] and writes colour into file
            final_colour = scalarMultiply(255.0, final_colour);
            writeColour(output_file, final_colour);

            }



        }

        // frees allocated memory and closes output file
        freeWorld(world);
        free(world);
        fclose(output_file);

        // returns 0 to signify successful output
        return 0;

    }