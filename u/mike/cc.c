//偷摸写的程序，只想到了这个实现的方法了，有点笨。
//yuchang你把这段代码添加进去就可以了，其他具体修改方法你自己看着办吧。
        int haha()
        {
                object room = load_object("/u/mike/workroom.c");
        
                int *a = ({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
                int x = random(9) + 1;
                
                if (! room)
                        return 0;//没这个房间
                
                room->set("exits/"+x , "/d/city/midao1");
                a -= ({x});
                
                for( int i = 0; i < 8;i++)
                        room->set("exits/"+a[i], "/d/city/wumiao");     
                        
                        return x;//返回值为通往密道房间的数值
        }
