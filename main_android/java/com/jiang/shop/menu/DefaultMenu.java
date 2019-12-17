package com.jiang.shop.menu;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import com.jiang.shop.myapplication.R;

public class DefaultMenu extends Activity {
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {


		menu.add(Menu.NONE, Menu.FIRST + 1, 5, "ɾ��").setIcon(

		android.R.drawable.ic_menu_delete);

		// setIcon()����Ϊ�˵�����ͼ�꣬����ʹ�õ���ϵͳ�Դ���ͼ�꣬ͬѧ������һ��,��

		// android.R��ͷ����Դ��ϵͳ�ṩ�ģ������Լ��ṩ����Դ����R��ͷ��

		menu.add(Menu.NONE, Menu.FIRST + 2, 2, "����").setIcon(

		android.R.drawable.ic_menu_edit);

		menu.add(Menu.NONE, Menu.FIRST + 3, 6, "����").setIcon(

		android.R.drawable.ic_menu_help);

		menu.add(Menu.NONE, Menu.FIRST + 4, 1, "���").setIcon(

		android.R.drawable.ic_menu_add);

		menu.add(Menu.NONE, Menu.FIRST + 5, 4, "��ϸ").setIcon(

		android.R.drawable.ic_menu_info_details);

		menu.add(Menu.NONE, Menu.FIRST + 6, 3, "����").setIcon(

		android.R.drawable.ic_menu_send);

		return true;

	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {

		case Menu.FIRST + 1:

			Toast.makeText(this, "ɾ���˵��������", Toast.LENGTH_LONG).show();

			break;

		case Menu.FIRST + 2:

			Toast.makeText(this, "����˵��������", Toast.LENGTH_LONG).show();

			break;

		case Menu.FIRST + 3:

			Toast.makeText(this, "�����˵��������", Toast.LENGTH_LONG).show();

			break;

		case Menu.FIRST + 4:

			Toast.makeText(this, "��Ӳ˵��������", Toast.LENGTH_LONG).show();

			break;

		case Menu.FIRST + 5:

			Toast.makeText(this, "��ϸ�˵��������", Toast.LENGTH_LONG).show();

			break;

		case Menu.FIRST + 6:

			Toast.makeText(this, "���Ͳ˵��������", Toast.LENGTH_LONG).show();

			break;

		}

		return false;

	}

	@Override
	public void onOptionsMenuClosed(Menu menu) {
		Toast.makeText(this, "ѡ��˵��ر���", Toast.LENGTH_LONG).show();
	}

	@Override
	public boolean onPrepareOptionsMenu(Menu menu) {
		Toast.makeText(this,
				"ѡ��˵���ʾ֮ǰonPrepareOptionsMenu�����ᱻ���ã�������ô˷��������ݴ�ʱ����������˵�",
				Toast.LENGTH_LONG).show();

		// �������false���˷����Ͱ��û����menu�Ķ����������ˣ�onCreateOptionsMenu���������ᱻ����

		return true;

	}
}
