//͵��д�ĳ���ֻ�뵽�����ʵ�ֵķ����ˣ��е㱿��
//yuchang�����δ�����ӽ�ȥ�Ϳ����ˣ����������޸ķ������Լ����Ű�ɡ�
        int haha()
        {
                object room = load_object("/u/mike/workroom.c");
        
                int *a = ({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
                int x = random(9) + 1;
                
                if (! room)
                        return 0;//û�������
                
                room->set("exits/"+x , "/d/city/midao1");
                a -= ({x});
                
                for( int i = 0; i < 8;i++)
                        room->set("exits/"+a[i], "/d/city/wumiao");     
                        
                        return x;//����ֵΪͨ���ܵ��������ֵ
        }
