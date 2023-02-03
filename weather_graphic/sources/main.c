#include "sorter.h"

int t_p_1(FILE *ptr, char file_name[100], int sorting_type, int sorting_order){

    int station_id;

    float data;

    char *n;
    n = malloc(sizeof(char));

    tree *root = NULL;

    int h = 0;

    while(fscanf(ptr, "%d %f", &station_id, &data) != EOF && sorting_type == '1'){

        root = insert_BST_node(sort_t_p_1, root, initialise_tree_node(station_id, "0", "0", n, data, 0));
    }

    while(fscanf(ptr, "%d %f", &station_id, &data) != EOF && sorting_type == '2'){

        root = insert_AVL_node(sort_t_p_1, root, initialise_tree_node(station_id, "0", "0", n, data, 0), &h);
    }

    while(fscanf(ptr, "%d %f", &station_id, &data) != EOF && sorting_type == '3'){

        root = insert_linked_list_node(sort_t_p_1, root, initialise_tree_node(station_id, "0", "0", n, data, 0));
    }

    fclose(ptr);

    root = apply_denominator(root);

    ptr = fopen(file_name, "w+");

    if(ptr == NULL){

        printf("ERROR :: exit path inaccessible (C)\n");

        exit(3);
    
    }
    
    if(sorting_order=='c'){
        t_p_1_output(ptr, root);
    }
    else{
        t_p_1_output_r(ptr, root);
    }

    fclose(ptr);

    return 0;

}

int t_p_2(FILE *ptr, char file_name[100], int sorting_type, int sorting_order){

    printf("ATTENTION :: this may take a while\n");

    float data;

    char date[26];

    tree *root = NULL;

    int h = 0;

    while(fscanf(ptr, "%s %f", date, &data) != EOF && sorting_type == '1'){

        root = insert_BST_node(sort_t_p_2, root, initialise_tree_node(1, "0", "0", date, data, 0));
    }

    while(fscanf(ptr, "%s %f", date, &data) != EOF && sorting_type == '2'){

        root = insert_AVL_node(sort_t_p_2, root, initialise_tree_node(1, "0", "0", date, data, 0), &h);
    }

    while(fscanf(ptr, "%s %f", date, &data) != EOF && sorting_type == '3'){

        root = insert_linked_list_node(sort_t_p_2, root, initialise_tree_node(1, "0", "0", date, data, 0));
    }

    fclose(ptr);

    root = apply_denominator(root);

    ptr = fopen(file_name, "w+");

    if(ptr == NULL){

        printf("ERROR :: exit path inaccessible (C)\n");

        exit(3);
    
    }
    
    if(sorting_order=='c'){
        t_p_2_output(ptr, root);
    }
    else{
        t_p_2_output_r(ptr, root);
    }

    fclose(ptr);

    return 0;

}

int t_p_3(FILE *ptr, char file_name[100], int sorting_type, int sorting_order){

    printf("ATTENTION :: this may take a while\n");

    int station_id;

    float data;

    char date[26];

    tree *root = NULL;
    int i = 0;

    int h = 0;

    while(fscanf(ptr, "%d %s %f", &station_id, date, &data) != EOF && sorting_type == '1'){

        root = insert_BST_node(sort_t_p_3, root, initialise_tree_node(station_id, "0", "0", date, data, 0)); 
    }

    while(fscanf(ptr, "%d %s %f", &station_id, date, &data) != EOF && sorting_type == '2'){

        root = insert_AVL_node(sort_t_p_3, root, initialise_tree_node(station_id, "0", "0", date, data, 0), &h);   
    }

    while(fscanf(ptr, "%d %s %f", &station_id, date, &data) != EOF && sorting_type == '3'){

        root = insert_linked_list_node(sort_t_p_3, root, initialise_tree_node(station_id, "0", "0", date, data, 0));
    }

    fclose(ptr);

    ptr = fopen(file_name, "w+");

    if(ptr == NULL){

        printf("ERROR :: exit path inaccessible (C)\n");

        exit(3);
    
    }
    
    if(sorting_order=='c'){
        t_p_3_output(ptr, root);
    }
    else{
        t_p_3_output_r(ptr, root);
    }

    fclose(ptr);

    return 0;

}

int wind(FILE *ptr, char file_name[100], int sorting_type, int sorting_order){

    int station_id;
    
    float rotation, speed;

    char X[26], Y[26];

    char *n;
    n = malloc(sizeof(char));

    tree *root = NULL;

    int h = 0;
    
    while(fscanf(ptr, "%d %s %s %f %f ", &station_id, X, Y, &rotation, &speed) != EOF && sorting_type == '1'){

        root = insert_BST_node(sort_wind, root, initialise_tree_node(station_id, X, Y, n, rotation, speed));
    }

    while(fscanf(ptr, "%d %s %s %f %f ", &station_id, X, Y, &rotation, &speed) != EOF && sorting_type == '2'){

        root = insert_AVL_node(sort_wind, root, initialise_tree_node(station_id, X, Y, n, rotation, speed), &h);
    }

    while(fscanf(ptr, "%d %s %s %f %f ", &station_id, X, Y, &rotation, &speed) != EOF && sorting_type == '3'){

        root = insert_linked_list_node(sort_wind, root, initialise_tree_node(station_id, X, Y, n, rotation, speed));
    }

    fclose(ptr);

    root = apply_denominator(root);

    ptr = fopen(file_name, "w+");

    if(ptr == NULL){

        printf("ERROR :: exit path inaccessible (C)\n");

        exit(3);
    
    }
    
    if(sorting_order=='c'){
        wind_output(ptr, root);
    }
    else{
        wind_output_r(ptr, root);
    }

    fclose(ptr);

    return 0;

}

int altitude(FILE *ptr, char file_name[100], int sorting_type, int sorting_order){

    int station_id;

    float altitude;

    char X[26], Y[26];

    char *n;
    n = malloc(sizeof(char));

    tree *root = NULL;

    int h = 0;

    while(fscanf(ptr, "%d %s %s %f", &station_id, X, Y, &altitude) != EOF && sorting_type == '2'){

        root = insert_AVL_node(sort_altitude, root, initialise_tree_node(station_id, X, Y, n, altitude, 0), &h);
    }

    while(fscanf(ptr, "%d %s %s %f", &station_id, X, Y, &altitude) != EOF && sorting_type == '1'){

        root = insert_BST_node(sort_altitude, root, initialise_tree_node(station_id, X, Y, n, altitude, 0));
    }

    while(fscanf(ptr, "%d %s %s %f", &station_id, X, Y, &altitude) != EOF && sorting_type == '3'){

        root = insert_linked_list_node(sort_altitude, root, initialise_tree_node(station_id, X, Y, n, altitude, 0));
    }

    fclose(ptr);

    ptr = fopen(file_name, "w+");

    if(ptr == NULL){

        printf("ERROR :: exit path inaccessible (C)\n");

        exit(3);
    
    }

    altitude_output(ptr, root);

    fclose(ptr);

    return 0;

}

int moisture(FILE *ptr, char file_name[100], int sorting_type, int sorting_order){

    int station_id;

    float moisture;

    char X[26], Y[26];

    char *n;
    n = malloc(sizeof(char));

    tree *root = NULL;

    int h = 0;

    while(fscanf(ptr, "%d %s %s %f", &station_id, X, Y, &moisture) != EOF && sorting_type == '1'){

        root = insert_BST_node(sort_moisture, root, initialise_tree_node(station_id, X, Y, n, moisture, 0));
    }

    while(fscanf(ptr, "%d %s %s %f", &station_id, X, Y, &moisture) != EOF && sorting_type == '2'){

        root = insert_AVL_node(sort_moisture, root, initialise_tree_node(station_id, X, Y, n, moisture, 0), &h);
    }

    while(fscanf(ptr, "%d %s %s %f", &station_id, X, Y, &moisture) != EOF && sorting_type == '3'){

        root = insert_linked_list_node(sort_moisture, root, initialise_tree_node(station_id, X, Y, n, moisture, 0));
    }

    fclose(ptr);

    ptr = fopen(file_name, "w+");

    if(ptr == NULL){

        printf("ERROR :: exit path inaccessible (C)\n");

        exit(3);
    
    }

    moisture_output(ptr, root);

    fclose(ptr);

    return 0;

}

int main(int argc, char *argv[]){

    // arguments are fetched in the following order

    //  entry path      exit path   data type   sorting type    sorting order
    //  argv[1]         argv[2]     argv[3]     argv[4]         argv[5]

    //Checks number of arguments
    if(argc != 6){
        printf("ERROR :: incorrect number of arguments (C)\n");
        exit(1);
    }

    //Creates entry path
    char path[100] = "temporary_files/";
    strcat(path, argv[1]);

    //Checks entry path
    FILE* ptr_entry = NULL;
    ptr_entry = fopen(path, "r");
    if(ptr_entry == NULL){

        printf("ERROR :: entry path inaccessible (C)\n");

        exit(2);

    }
    
    //create exit path
    char path2[100] = "sorted_weather_data/";
    strcat(path2, argv[2]);

    char sorting_order;

    //initialises sorting order variable
    switch (*argv[5])
    {
    case 'r':
        sorting_order = 'r';
        break;
    
    default:
        sorting_order = 'c';
        break;
    }

    //Checks sorting type
    int sorting_type = *argv[4];
    if(sorting_type < '1' || sorting_type > '3'){

        printf("ERROR :: fetched sorting type out of range (C)\n");

        exit(1);

    }
    
    //Calls sorting function
    switch (*argv[3])
    {
    case '1':
        t_p_1(ptr_entry, path2, sorting_type, sorting_order);
        break;
    
    case '2':
        t_p_2(ptr_entry, path2, sorting_type, sorting_order);
        break;
    
    case '3':
        t_p_3(ptr_entry, path2, sorting_type, sorting_order);
        break;
    
    case 'w':
        wind(ptr_entry, path2, sorting_type, sorting_order);
        break;
    
    case 'h':
        altitude(ptr_entry, path2, sorting_type, sorting_order);
        break;

    case 'm':
        moisture(ptr_entry, path2, sorting_type, sorting_order);
        break;

    default:
        printf("ERROR :: fetched data type argument is incorrect (C)");
        exit(1);
        break;
    }

    return 0;
}