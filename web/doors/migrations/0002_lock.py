# Generated by Django 2.2 on 2019-05-11 19:04

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('doors', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='Lock',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('hwid', models.IntegerField()),
                ('controller', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='doors.Controller')),
            ],
        ),
    ]
