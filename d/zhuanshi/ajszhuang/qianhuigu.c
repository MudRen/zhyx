// ǧ�ع��Թ� copyright by yuchang

// inherit VRM_SERVER;

inherit __DIR__"vrm_server";

void create()
{
        // �Թ��������̳е�����ĵ������ơ�
        set_inherit_room( ROOM );

        //�Թ�������Ĺ��
        set_maze_npcs(__DIR__"npc/guard");

        //�Թ��ĵ��߳�
        set_maze_long(33);

        //��ڷ���(�����ڶ���)
        set_entry_dir("east");

        //�������������ӷ���
        set_link_entry_dir("east");

        //�������������ӵ�����
        set_link_entry_room(__DIR__"shanlu");

        //��������������ӷ���
        set_link_exit_dir("west");

        //��������������ӵ�����
        set_link_exit_room(__DIR__"shanzhuang");

        //��ڷ��������
        set_entry_short("ɽ·");

        //��ڷ�������
        set_entry_desc(@LONG
�������Ӳݴ����Ļ�Ұ֮���ˣ����ܾ����ĵ�,
����û���κ���������һ�㣬����������ֻ����
���ܷ�����΢�紵�����ַ���ɳɳ��������
LONG);

        //���ڷ��������
        set_exit_short("��Ұ");

        //���ڷ�������
        set_exit_desc(@LONG
����ǰһ������������˿��������������ǳ����ˡ�����С��
���������ͷ紵�����ֵ�ɳɳ����֯�������Ĵ���Ȼ�����ɡ�
LONG
);

        //�Թ�����Ķ�����
        set_maze_room_short("ǧ�ع�");

        //�Թ����������������ж�������������ÿ����
        //���ʱ���������ѡ��һ����
        set_maze_room_desc(@LONG
���Ǹ���Ͽ�ȣ������������������㵨���ľ�����ǰ�����ţ�������һЩ
��·�˵�ʬ������á���ʱ����һ�������˺�,������ʲô
�����ڰ��п����ţ��㲻�ɵļӿ��˽Ų���
LONG
);

        // �Թ������Ƿ�Ϊ���ⷿ�䣿
        set_outdoors(1);
}


