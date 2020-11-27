void init()
{
        add_action("do_look","look");
        add_action("do_type","type");
}

int do_look(string arg)
{
        int i;
        string msg;
        mapping *bang_quest,*bang_zs;

        if (!arg || arg != "paizi")
                return 0;

        bang_zs = PARTY_QUEST_D->query_zhuisha_quest(TYPE);
        bang_quest = PARTY_QUEST_D->query_city_quest(PLACE,TYPE);
        bang_zs = sort_array(bang_zs,(: sort_by_id :));
        bang_quest = sort_array(bang_quest,(: sort_by_id :));

        msg = HIC "----------------------------------------------------------------------------\n"NOR;
        msg += WHT BBLU "                                  ׷ɱ��                                    \n"NOR;
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        msg += sprintf(HIR"%-10s%-50s%-10s%s\n"NOR,"���","����","�Ѷ�","����");
        if (sizeof(bang_zs))
                for (i=0;i<sizeof(bang_zs);i++)
                        msg += sprintf("%-10s%-50s%-10s%s\n",
                                          bang_zs[i]["id"],
                                          "׷ɱ"+bang_zs[i]["name"],
                                          bang_zs[i]["difficult"],
                                          bang_zs[i]["reward"],
                                      );
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        msg += WHT BBLU "                                  �����                                    \n"NOR;
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        msg += sprintf(HIR"%-10s%-50s%-10s%s\n"NOR,"���","����","�Ѷ�","����");
        if (sizeof(bang_quest))
                for (i=0;i<sizeof(bang_quest);i++)
                {
                        if (bang_quest[i]["id"] == "xc" && !bang_quest[i]["enable"]) continue;
                        msg += sprintf("%-10s%" + sprintf("%d", (50 + color_len(bang_quest[i]["name"]))) + "-s%-10s%s\n",
                                          bang_quest[i]["id"],
                                          bang_quest[i]["name"],
                                          bang_quest[i]["difficult"],
                                          bang_quest[i]["reward"],
                                      );
                }
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        msg += HIC "����type <���>�鿴ÿ������ľ��������\n"NOR;
        msg += HIC "����choose <���>ѡ����Ҫ��ɵ����񣬷���������giveupָ�\n"NOR;

        this_player()->start_more(msg);
        return 1;
}

int do_type(string arg)
{
        string msg;
        mapping bang_quest;

        if (!wizardp(this_player()) &&  
            (this_player()->query("bang_bad") || this_player()->query("shen") < 0))
                return notify_fail("��һ���ڵ���ʿ����������ʲô����\n");

        if (!wizardp(this_player()) && !this_player()->query("bang_good"))
                return notify_fail("���ȼ���׵����ˣ��ſ��Բ鿴�׵�������\n");

        if (!arg) 
                return notify_fail("����鿴�����������ϸ��Ϣ��ָ�type <���>\n");

        bang_quest = PARTY_QUEST_D->query_zhuisha_quest(TYPE,arg);

        if (!bang_quest)     
                bang_quest = PARTY_QUEST_D->query_city_quest(PLACE,TYPE,arg);

        if (!bang_quest)
                return notify_fail("������ѯ�ı��Ϊ"+arg+"�����񲢲����ڡ�\n");
        
/*      if (bang_quest["id"] == "xc" && !bang_quest["enable"]) 
                return notify_fail("�����Ѿ��е���ȥѲ���ˣ���ȸ���ɡ�\n");
*/
        msg = HIC "\n----------------------------------------------------------------------------\n"NOR;
        msg += "�����ţ�" + bang_quest["id"] + "\n";
        msg += "�������ͣ�" + bang_quest["type"] + "\n";
        msg += "�������ƣ�" + bang_quest["name"] + "\n";
        msg += "�����Ѷȣ�" + bang_quest["difficult"] + "\n";
        msg += "��������" + bang_quest["reward"] + "\n";
        msg += "������Ϣ: \n" + bang_quest["msg"] + "\n";
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        this_player()->start_more(msg);
        return 1;
}

int sort_by_id(mapping quest1, mapping quest2)
{
          return strcmp(quest1["id"], quest2["id"]);
}


