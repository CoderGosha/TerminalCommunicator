# Generated by Django 3.2.8 on 2021-11-29 09:08

import datetime
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Communicator', '0015_auto_20211120_1740'),
    ]

    operations = [
        migrations.AddField(
            model_name='event',
            name='data_expired',
            field=models.DateTimeField(blank=True, default=datetime.datetime(2021, 11, 29, 12, 8, 10, 149422), null=True),
        ),
        migrations.AlterField(
            model_name='event',
            name='data_create',
            field=models.DateTimeField(default=datetime.datetime(2021, 11, 29, 12, 8, 10, 149422)),
        ),
    ]