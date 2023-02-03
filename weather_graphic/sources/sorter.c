#include "sorter.h"

/*
Nodewise operations, check .h file for further information
*/

//initialises node for any insertion function
tree* initialise_tree_node(int station_id, char X[26], char Y[26], char date[26], float data, float data2){

    tree *new_node = malloc(sizeof(tree));

    new_node->station_id = station_id;

    //Stocks date
    new_node->date = malloc(26 * sizeof(char));
    strcpy(new_node->date, date);

    //Stocks coordinate data
    new_node->X = malloc(26 * sizeof(char));
    new_node->Y = malloc(26 * sizeof(char));
    strcpy(new_node->X, X);
    strcpy(new_node->Y, Y);

    new_node->data1 = data;
    new_node->data2 = data2;
    new_node->data_min = data;
    new_node->data_max = data;

    new_node->denominator = 1;

    new_node->right = NULL;
    new_node->left = NULL;

    new_node->equilibrium = 0;

    return new_node;

}

//standard BST insertion algorithm with function pointer pointing to order feedback function
//check .h file for further information
tree* insert_BST_node(int (*s)(tree*, tree*), tree *node, tree *new_node){

    if(node == NULL){
        node = new_node;
        return node;
    }

    //Does not allow duplicates, deletes node
    if((*s)(node, new_node) == 0){
        free(new_node);
        return node;
    }

    //Merges nodes and increases denominator for the computation of average values later on
    if((*s)(node, new_node) == 3){

        node->data1 += new_node->data1;
        node->data2 += new_node->data2;
        node->denominator++;

        if(node->data_min > new_node->data1){
            node->data_min = new_node->data1;
        }

        if(node->data_max < new_node->data1){
            node->data_max = new_node->data1;
        }

        return node;

    }

    //Recalls function with left node
    if((*s)(node, new_node) == 2){
        node->left = insert_BST_node(s, node->left, new_node);
        return node;
    }

    //Recalls function with right node
    if((*s)(node, new_node) == 1){
        node->right = insert_BST_node(s, node->right, new_node);
        return node;
    }

}

//standard linked list insertion algorithm with function pointer pointing to order feedback function
//check .h file for further information
//Nearly dentical to BST function for practicality purposes 
tree* insert_linked_list_node(int (*s)(tree*, tree*), tree* node, tree *new_node){

    if(node == NULL){
        node = new_node;
        return node;
    }

    if((*s)(node, new_node) == 0){
        free(new_node);
        return node;
    }

    if((*s)(node, new_node) == 3){

        node->data1 += new_node->data1;
        node->data2 += new_node->data2;
        node->denominator++;

        if(node->data_min > new_node->data1){
            node->data_min = new_node->data1;
        }

        if(node->data_max < new_node->data1){
            node->data_max = new_node->data1;
        }

        free(new_node);

        return node;

    }

    if((*s)(node, new_node) == 2){
        tree *temp = node;
        node = new_node;
        new_node->right = temp;
        return node;
    }

    if((*s)(node, new_node) == 1){
        node->right = insert_linked_list_node(s, node->right, new_node);
        return node;
    }

}

//standard AVL insertion algorithm with function pointer pointing to order feedback function
//check .h file for further information
tree* insert_AVL_node(int (*s)(tree*, tree*), tree* node, tree *new_node, int *h){

    if(node == NULL){
        node = new_node;
        *h = 1;
        return node;
    }

    //Recalls function with left node
    else if((*s)(node, new_node) == 2){
        node->left = insert_BST_node(s, node->left, new_node);
        *h = -(*h);
    }

    //Recalls function with right node
    else if((*s)(node, new_node) == 1){
        node->right = insert_BST_node(s, node->right, new_node);
    }

    //Merges nodes and increases denominator for the computation of average values later on
    else if((*s)(node, new_node) == 3){

        node->data1 += new_node->data1;
        node->data2 += new_node->data2;
        node->denominator++;

        if(node->data_min > new_node->data1){
            node->data_min = new_node->data1;
        }

        if(node->data_max < new_node->data1){
            node->data_max = new_node->data1;
        }

        *h = 0;
        return node;

    }

    //Does not allow duplicates, deletes node
    else if((*s)(node, new_node) == 0){
        free(new_node);
        *h = 0;
        return node;
    }

    if(*h != 0){
        node->equilibrium = node->equilibrium + *h;
        node = calibrate(node);
        if(node->equilibrium == 0){
            *h = 0;
        }
        else{
            *h = 1;
        }
    }

    return node;

}

tree* calibrate(tree *node){

    if(node->equilibrium >= 2){
        if(node->right->equilibrium >= 0) return rotate_left(node);
        return double_rotate_left(node);
    }

    else if(node->equilibrium <= -2){
        if(node->left->equilibrium <= 0) return rotate_right(node);
        return double_rotate_right(node); 
    }

    return node;

}

tree* rotate_left(tree *node){

    tree* temp = node->right;
    node->right = temp->left;
    temp->left = node;

    int eq_temp = temp->equilibrium, eq_node = node->equilibrium;
    node->equilibrium = eq_node - max(eq_temp, 0) - 1;
    temp->equilibrium = min(min(eq_node - 2, eq_node + eq_temp - 2), eq_temp - 1);
    
    node = temp;
    return node;

}

tree* rotate_right(tree *node){

    tree* temp = node->left;
    node->left = temp->right;
    temp->right = node;

    int eq_temp = temp->equilibrium, eq_node = node->equilibrium;
    node->equilibrium = eq_node - min(eq_temp, 0) + 1;
    temp->equilibrium = max(max(eq_node + 2, eq_node + eq_temp + 2), eq_temp + 1);
    
    node = temp;
    return node;

}

tree* double_rotate_left(tree *node){

    node->right = rotate_right(node->right);

    return rotate_left(node);

}

tree* double_rotate_right(tree *node){

    node->left = rotate_left(node->left);

    return rotate_right(node);

}

/*
Feedback functions, check .h file for further information
*/

int sort_t_p_1(tree *node, tree *new_node){

    if(node->station_id == new_node->station_id) return 3;

    if(node->station_id > new_node->station_id) return 2;

    if(node->station_id < new_node->station_id) return 1;

}

int sort_t_p_2(tree *node, tree *new_node){

    if(strcmp(node->date, new_node->date) == 0) return 3;

    if(strcmp(node->date, new_node->date) > 0) return 2;

    if(strcmp(node->date, new_node->date) < 0) return 1;

    return 0;

}

int sort_t_p_3(tree *node, tree *new_node){

    if(strcmp(node->date, new_node->date) == 0){
        if(node->station_id > new_node->station_id) return 2;
        if(node->station_id < new_node->station_id) return 1;
    }

    if(strcmp(node->date, new_node->date) > 0) return 2;

    if(strcmp(node->date, new_node->date) < 0) return 1;

    return 0;

}

int sort_wind(tree *node, tree *new_node){

    if(node->station_id == new_node->station_id) return 3;

    if(node->station_id > new_node->station_id) return 2;

    if(node->station_id < new_node->station_id) return 1;

}

int sort_altitude(tree *node, tree *new_node){

    if(node->station_id == new_node->station_id) return 0;

    if(node->data1 >= new_node->data1) return 2;

    if(node->data1 < new_node->data1) return 1;

}

int sort_moisture(tree *node, tree *new_node){

    if(node->station_id == new_node->station_id) return 3;

    if(node->station_id > new_node->station_id) return 2;

    if(node->station_id < new_node->station_id) return 1;

}

/*
Output operations, check .h file for further information
*/

void wind_output(FILE *ptr, tree* node){

    if(node==NULL) return;

    wind_output(ptr, node->left);

    fprintf(ptr, "%s %s %f %f\n\n", node->X, node->Y, node->data1, node->data2);

    wind_output(ptr, node->right);

    free(node);

}

void wind_output_r(FILE *ptr, tree* node){

    if(node==NULL) return;

    wind_output(ptr, node->right);

    fprintf(ptr, "%s %s %f %f\n\n", node->X, node->Y, node->data1, node->data2);

    wind_output(ptr, node->left);

    free(node);

}

void altitude_output(FILE *ptr, tree* node){

    if(node==NULL) return;

    altitude_output(ptr, node->right);

    fprintf(ptr, "%s %s %f\n\n", node->X, node->Y, node->data1);

    altitude_output(ptr, node->left);

    free(node);

}

void moisture_output(FILE *ptr, tree *node){

    if(node==NULL) return;

    moisture_output(ptr, node->left);

    fprintf(ptr, "%s %s %f\n\n", node->X, node->Y, node->data_max);

    moisture_output(ptr, node->right);

    free(node);

}

void t_p_1_output(FILE *ptr, tree* node){

    if(node==NULL) return;

    t_p_1_output(ptr, node->left);

    fprintf(ptr, "%d %.5f %.5f %.5f\n\n", node->station_id, node->data1, node->data_min, node->data_max);

    t_p_1_output(ptr, node->right);

    free(node);

}

void t_p_1_output_r(FILE *ptr, tree* node){

    if(node==NULL) return;

    t_p_1_output(ptr, node->right);

    fprintf(ptr, "%d %.5f %.5f %.5f\n\n", node->station_id, node->data1, node->data_min, node->data_max);

    t_p_1_output(ptr, node->left);

    free(node);

}

void t_p_2_output(FILE *ptr, tree* node){

    if(node==NULL) return;

    t_p_2_output(ptr, node->left);

    fprintf(ptr, "%s %f\n\n", node->date, node->data1);

    t_p_2_output(ptr, node->right);

    free(node);

}

void t_p_2_output_r(FILE *ptr, tree* node){

    if(node==NULL) return;

    t_p_2_output(ptr, node->right);

    fprintf(ptr, "%s %f\n\n", node->date, node->data1);

    t_p_2_output(ptr, node->left);

    free(node);

}

void t_p_3_output(FILE *ptr, tree* node){

    if(node==NULL) return;

    t_p_3_output(ptr, node->left);

    fprintf(ptr, "%d %s %f\n\n", node->station_id, node->date, node->data1);

    t_p_3_output(ptr, node->right);

    free(node);

}

void t_p_3_output_r(FILE *ptr, tree* node){

    if(node==NULL) return;

    t_p_3_output(ptr, node->right);

    fprintf(ptr, "%d %s %f\n\n", node->station_id, node->date, node->data1);

    t_p_3_output(ptr, node->left);

    free(node);

}

/*
Other functions
*/

//used to compute node average
tree* apply_denominator(tree *node){

    if(node == NULL) return NULL;

    node->left = apply_denominator(node->left);

    node->data1 /= node->denominator;
    node->data2 /= node->denominator;

    node->right = apply_denominator(node->right);

    return node;

}

int max(int a, int b){

    if(a > b) return a;

    return b;

}

int min(int a, int b){

    if(a < b) return a;

    return b;

}
