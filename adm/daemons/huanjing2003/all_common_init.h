// ���ļ��� all_room_info_hj.h
// �� 1_room_info_special.h 
// ��  void init() �ڵ��á�

// naihe 0:29 03-10-21


// ��������ǰ�� {} ���������ﶼ�ǲ���Ҫ�ģ���������ڸ����ӣ���������Щ
//void init()
//{

    object me = this_player();

    if( me->query_temp("huanjing") !="start" && !me->query("hj_game/npc") )
    {
        remove_call_out("get_out_here");
        call_out("get_out_here",1, me);
    }
    // �������Ϸʱ������������״̬������
    if( me->query_temp("huanjing") == "start" )
        full_all( me );

    if( query("room_mark") != 1 && me->query("hj_game/npc") )
        return;
// ������� 1 �ŷ��䣬�������� NPC �Ļ���ֱ�� return ���ˣ����
// add_action() �ܺ���Դ��
// ����NPC����Ҫ����һЩ�����Ķ����������������� return ��

    // ��ֹ��ָ��
    add_action( "block_cmds", ({
        "exercise", "dazuo", "respirate",
        "tuna", "practice", "lian",  "exert",
        "study", "du", 
        "eat", "chi", "drink", "he", "fu",
        "to", "scheme", "put",
        "paimai", "jiaoyi", "paimai*", "jiaoyi*",
        "kill", "yun", "pfm", "perform", "hit", "throw", "shoot", "steal", "fight",
        "score", "hp", "hp2", "score2", "score3", "scorenew", "jifa", "enable",
        "jiali", "jiajin", "enforce", "enpower", "prepare", "bei", "inventory",
        "xue", "learn", "skills", "cha", "quest", "questobj",
        "wield", "unwield", "wear", "remove", 
        "new", "new*", "menpai", "menpai*", "jiaoyi", "jiaoy*", "rumor", "rumor*",
        "bangpai", "bangpai*", 
    }) );
    add_action("do_look","look");
    add_action("do_get","get");
//}
