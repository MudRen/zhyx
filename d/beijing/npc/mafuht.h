int do_rideht()
{
	string hname;
	object ob = this_player();
	if (ob->query_temp("marks/horserent")!=1 && ob->query("age")>14)
                return notify_fail("С���Ӳſ������������Ҫ��Ǯ��\n");
	switch (random(3))
	{
		case 1:
			hname=MAG"������"NOR;
			break;
		case 2:
			hname=RED"�����"NOR;
			break;
		default:
			hname=HIY"������"NOR;
			break;
	}
	message_vision(
"������ָ�$Nǣ��һƥ"+hname+"��$N����Ծ��������������������·������һ��
���: �����ޡ�\n"NOR , ob );
	message_vision("\nֻ��$N������һ�У�"+hname+"�����͵��ȥ��\n",ob);
	ob->move("/d/beijing/niaoshi");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/xi_1");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/xi_2");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/caroad_w2");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/cagc_w");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/tiananmen");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/cagc_e");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/caroad_e1");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/wang_1");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/wang_2");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/wang_4");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/chaoyang_dao1");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/chaoyang_dao2");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/chaoyangmen");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/road1");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/road2");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/beijing/road3");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/laolongtou");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/shanhaiguan");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/road1");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/road2");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/road3");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/ningyuan");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/road4");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/road5");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/road6");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/road7");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/road8");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/muqiao");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/nancheng");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/jishi");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·��ҡ���۶�����\n", ({ob}));
	ob->move("/d/guanwai/majiu");
	tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·˳�������ͼ������\n");
	message_vision("\n$N����һת��Ծ����������̬ʮ������������Ҳ��$Nһ��� !\n" ,ob);
	ob->delete_temp("marks/horserent");
	return 1;
}
