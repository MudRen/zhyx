//wjb_hzdamen.c

inherit ROOM;

void create()
{ 
        set("short", "�޼��ﺼ�ݷֶ�");
        set("long",@LONG
�������޼��ﺼ�ݷֶ�Ĵ���ǰ�棬�ڽ���һ�����޼�������
�ƴ����Ʋ������ɾ�����������ҵĴ��¡�
LONG );
        set("outdoors", "xiangyang");
        set("exits", ([  
                "east"  :  __DIR__"road12",
                "west"  :  __DIR__"wjb_hzfb",
        ])); 
        set("objects", ([   
             "/d/xiangyang/npc/wjb-guard" : 2,   
        ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "west") 
        {
           if (! me->query_temp("good_wjb") && me->query("bang_good/name") != "�޼���")
               return notify_fail("����һ����ס�㣬�����ȵ������޼������������˵���������\n"); 
           else
           {
              me->delete_temp("good_wjb");
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 

