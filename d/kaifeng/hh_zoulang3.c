inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���Ǻ컨���ܶ��ڵ�һ��ľ�Ƶ����ȣ����������ǹ⻬
�������ȱ�������һ����Ⱦ���㲻ʱ�ܹ����������컨��Ļ�
�ڻ��ǵ����ڴ��߶���æµ����ͣ��
LONG);
        set("no_clean_up", 0);
        set("exits", ([
  		"west" : __DIR__"hh_qianting",
  		"east" : __DIR__"hh_pianting2",
	]));
        setup();
        //replace_program(ROOM);
}