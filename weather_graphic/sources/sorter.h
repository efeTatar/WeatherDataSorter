/*
    sorter.h header file
*/

#ifndef SORTER_H
    #define SORTER_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>



    /*
    Structures
    */

    //structure used in all insertion operations
    //contains every necessary data
    typedef struct tree{

        int station_id;

        char *X, *Y;

        char *date;

        float data1, data2, data_min, data_max;

        int denominator;

        struct tree *right, *left;

        int equilibrium;

    }tree;



    /*
    Functions
    Check node.c file for further information on each function
    */

    /*
    Nodewise operations
    */

    //function used to initialise node
    tree*   initialise_tree_node        (int station_id, char X[26], char Y[26], char *date, float data, float data2);

    //creates binary search tree
    tree*   insert_BST_node             (int (*s)(tree*, tree*), tree* node, tree *new_node);

    //creates linked list
    tree*   insert_linked_list_node     (int (*s)(tree*, tree*), tree* node, tree *new_node);

    //AVL insertion function and its subfunctions
    //creates AVL tree
    tree*   insert_AVL_node             (int (*s)(tree*, tree*), tree* node, tree *new_node, int *h);

    tree*   rotate_left                 (tree *node);

    tree*   rotate_right                (tree *node);

    tree*   double_rotate_right         (tree *node);

    tree*   double_rotate_left          (tree *node);

    tree*   calibrate                   (tree *node);

    //apply_denominator is used when station average is needed
    tree*   apply_denominator           (tree *node);

    /*
    Order feedback functions
    These operations determine the behaviour of the 3 insertion functions
    They can determine if nodes are to be deleted, inserted or merged
    */

    int     sort_t_p_1                  (tree *node, tree *new_node);

    int     sort_t_p_2                  (tree *node, tree *new_node);

    int     sort_t_p_3                  (tree *node, tree *new_node);

    int     sort_wind                   (tree *node, tree *new_node);

    int     sort_altitude               (tree *node, tree *new_node);

    int     sort_moisture               (tree *node, tree *new_node);

    /*
    Filewise operations
    These operations copies node data to a given file
    either in a given order
    r -> decreasing
    */

    void    t_p_1_output                (FILE *ptr, tree *node);

    void    t_p_1_output_r              (FILE *ptr, tree *node);

    void    t_p_2_output                (FILE *ptr, tree *node);

    void    t_p_2_output_r              (FILE *ptr, tree *node);

    void    t_p_3_output                (FILE *ptr, tree* node);

    void    t_p_3_output_r              (FILE *ptr, tree* node);

    void    wind_output                 (FILE *ptr, tree *node);

    void    wind_output_r               (FILE *ptr, tree *node);

    void    altitude_output             (FILE *ptr, tree *node);

    void    moisture_output             (FILE *ptr, tree *node);

    /*
    Other functions
    */
   
    int     max                         (int a, int b);

    int     min                         (int a, int b);



#endif