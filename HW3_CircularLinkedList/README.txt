{\rtf1\ansi\ansicpg950\cocoartf1671
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww21600\viewh15140\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\f0\fs48 \cf0 This is a program about Russian Roulette.\
When you execute the program , it will show you three options that 1 means read data from a file,2 means append new nodes by yourself, and 3 means exit if you don\'92t want to continue executing anymore.\
\
Here is the program executing process.\
First,you should deliver a file about people who may be killed or input them by yourself.The program will show the list data after you compelete it.\
Second,you should input the killing direction between right or left.\
Third,you should input the skip number, and then the program will show the killing process.\
\
Here is the program\'92s algorithm:\
This program use \'93doubly circular linked list\'94 to store the datas by \'93adding\'94 newnode after the original node, so you can follow either right or left direction to kill the data.\
The doubly circular linked list contains a headnode.\
After the user key in the direction and the skip number, the program will follow these rules to find the next person who will be killed and then \'93delete\'94 it from the doubly circular linked list until the data list equals to 1.\
\
}