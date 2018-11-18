#include <math.h>

struct Matrix4 {
    float m[4][4];

    Matrix4(){
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                m[i][j] = 0;
            }
        }
    }

    Matrix4(float v){
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(i == j)
                    m[i][i] = v;
                else
                    m[i][j] = 0;
            }
        }
    }

    Matrix4(float v[4][4]){
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                m[i][j] = v[i][j];
            }
        }
    }
    

    void makeIdentity(){
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(i == j)
                    m[i][i] = 1;
                else
                    m[i][j] = 0;
            }
        }
    }

    /*void multiply(Matrix4 mat){
        m[0][0] = (m[0][0] * mat.m[0][0]) + (m[1][0] * mat.m[0][1]) + (m[2][0] * mat.m[0][2]) + (m[3][0] * mat.m[0][3]);
        m[0][1] = (m[0][1] * mat.m[0][0]) + (m[1][1] * mat.m[0][1]) + (m[2][1] * mat.m[0][2]) + (m[3][1] * mat.m[0][3]);
        m[0][2] = (m[0][2] * mat.m[0][0]) + (m[1][2] * mat.m[0][1]) + (m[2][2] * mat.m[0][2]) + (m[3][2] * mat.m[0][3]);
        m[0][3] = (m[0][3] * mat.m[0][0]) + (m[1][3] * mat.m[0][1]) + (m[2][3] * mat.m[0][2]) + (m[3][3] * mat.m[0][3]);

        m[1][0] = (m[0][0] * mat.m[1][0]) + (m[1][0] * mat.m[1][1]) + (m[2][0] * mat.m[1][2]) + (m[3][0] * mat.m[1][3]);
        m[1][1] = (m[0][1] * mat.m[1][0]) + (m[1][1] * mat.m[1][1]) + (m[2][1] * mat.m[1][2]) + (m[3][1] * mat.m[1][3]);
        m[1][2] = (m[0][2] * mat.m[1][0]) + (m[1][2] * mat.m[1][1]) + (m[2][2] * mat.m[1][2]) + (m[3][2] * mat.m[1][3]);
        m[1][3] = (m[0][3] * mat.m[1][0]) + (m[1][3] * mat.m[1][1]) + (m[2][3] * mat.m[1][2]) + (m[3][3] * mat.m[1][3]);

        m[2][0] = (m[0][0] * mat.m[2][0]) + (m[1][0] * mat.m[2][1]) + (m[2][0] * mat.m[2][2]) + (m[3][0] * mat.m[2][3]);
        m[2][1] = (m[0][1] * mat.m[2][0]) + (m[1][1] * mat.m[2][1]) + (m[2][1] * mat.m[2][2]) + (m[3][1] * mat.m[2][3]);
        m[2][2] = (m[0][2] * mat.m[2][0]) + (m[1][2] * mat.m[2][1]) + (m[2][2] * mat.m[2][2]) + (m[3][2] * mat.m[2][3]);
        m[2][3] = (m[0][3] * mat.m[2][0]) + (m[1][3] * mat.m[2][1]) + (m[2][3] * mat.m[2][2]) + (m[3][3] * mat.m[2][3]);

        m[3][0] = (m[0][0] * mat.m[3][0]) + (m[1][0] * mat.m[3][1]) + (m[2][0] * mat.m[3][2]) + (m[3][0] * mat.m[3][3]);
        m[3][1] = (m[0][1] * mat.m[3][0]) + (m[1][1] * mat.m[3][1]) + (m[2][1] * mat.m[3][2]) + (m[3][1] * mat.m[3][3]);
        m[3][2] = (m[0][2] * mat.m[3][0]) + (m[1][2] * mat.m[3][1]) + (m[2][2] * mat.m[3][2]) + (m[3][2] * mat.m[3][3]);
        m[3][3] = (m[0][3] * mat.m[3][0]) + (m[1][3] * mat.m[3][1]) + (m[2][3] * mat.m[3][2]) + (m[3][3] * mat.m[3][3]);
    }*/
    void multiply(Matrix4 mat) { //multiplies the THIS matrix by m1, in that order
        float tempSum = 0;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 4; k++) {
                    tempSum += m[i][k]*mat.m[k][j];
                }
                m[i][j] = tempSum;
                tempSum = 0;
            }
        }
    }


    static Matrix4 multiply(Matrix4 m1, Matrix4 m2) {
        Matrix4 matAns;
        float  tempSum = 0;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 4; k++) {
                    tempSum += m1.m[i][k]*m2.m[k][j];
                }
                matAns.m[i][j] = tempSum;
                tempSum = 0;
            }
        }
        return matAns;
    }

    void setOrthoganalProjectionMatrix(float left, float right, float bottom, float top){
        m[0][0] = 2 / (right - left);
        m[1][1] = 2 / (top - bottom);
        m[3][0] = -((right + left) / (right - left));
        m[3][1] = -((top + bottom) / (top - bottom));
    }

    void setPerspectiveProjectionMatrix(float left, float right, float bottom, float top, float near, float far) {
        m[0][0] = 2*near/(right - left); m[0][2] = (right + left)/(right - left);
        m[1][1] = 2*near/(top - bottom); m[1][2] = (top + bottom)/(top - bottom);
        m[2][2] = -(far + near)/(far - near); m[2][3] = -2*(far*near)/(far - near);
        m[3][2] = -1; m[3][3] = 0;
    }

    void scale2D(float x, float y){
        m[0][0] = x;
        m[1][1] = y;
    }

    void translate2D(float x, float y){
        m[3][0] += x;
        m[3][1] += y;
    }

    void rotateX(float amt){
        Matrix4 rot(1);
        rot.m[1][1] = cos(amt);
        rot.m[2][2] = cos(amt);
        rot.m[2][1] = -sin(amt);
        rot.m[1][2] =  sin(amt);
        *this = multiply(rot, *this);
    }
    
    void rotateY(float amt){
        Matrix4 rot(1);
        rot.m[0][0] = cos(amt);
        rot.m[2][2] = cos(amt);
        rot.m[2][0] = sin(amt);
        rot.m[0][2] = -sin(amt);
        *this = multiply(rot, *this);
    }
    
    void rotateZ(float amt){
        Matrix4 rot(1);
        rot.m[0][0] = cos(amt);
        rot.m[1][1] = cos(amt);
        rot.m[1][0] = -sin(amt);
        rot.m[0][1] =  sin(amt);
        *this = multiply(rot, *this);
    }
};