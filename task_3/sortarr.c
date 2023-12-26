#include <Python.h>

#define MIN_MERGE 32

int min(int a, int b){
    if (a < b) {
        return a;
    }
    else {
        return b;
   }
}

void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int left, int mid, int right) {
    int len1 = mid - left + 1, len2 = right - mid;
    int* left_arr = (int*)malloc(len1 * sizeof(int));
    int* right_arr = (int*)malloc(len2 * sizeof(int));

    memcpy(left_arr, &arr[left], len1 * sizeof(int));
    memcpy(right_arr, &arr[mid + 1], len2 * sizeof(int));

    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        }
        else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < len2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }

    free(left_arr);
    free(right_arr);
}

void tim_sort(int arr[], int n) {
    for (int i = 0; i < n; i += MIN_MERGE)
        insertionSort(arr, i, min((i + MIN_MERGE - 1), (n - 1)));

    for (int size = MIN_MERGE; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            merge(arr, left, mid, right);
        }
    }
}




static PyObject *c_sort(PyObject *self, PyObject *args) {
    PyObject *input_list;
    if (!PyArg_ParseTuple(args, "O", &input_list)) {
        return NULL;
    }

    Py_ssize_t size = PyList_Size(input_list);

    int* arr = malloc(size * sizeof(int));
    for (Py_ssize_t i = 0; i < size; i++) {
        arr[i] = (int)PyLong_AsLong(PyList_GetItem(input_list, i));
    }

    tim_sort(arr, size);

    PyObject* sorted_list = PyList_New(size);

    for (Py_ssize_t i = 0; i < size; i++) {
        PyList_SET_ITEM(sorted_list, i, PyLong_FromLong(arr[i]));
    }

    free(arr);

    return sorted_list;
}

static PyMethodDef module_methods[] = {
    {"c_sort", c_sort, METH_VARARGS, "sorts int values"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module_definition = {
    PyModuleDef_HEAD_INIT,
    "sortarr.c",
    "sorts int values",
    -1,
    module_methods
};

PyMODINIT_FUNC PyInit_sortarr(void) {
    return PyModule_Create(&module_definition);
}