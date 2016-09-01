# -*- coding: utf-8 -*-



categories=('Car','Bike','Book','Music','Outdoors','Household','Misc.')

db.define_table('listing',
   Field('title', unique=True, requires=IS_NOT_EMPTY()),
   Field('phone_number', requires=IS_NOT_EMPTY()),
   Field('category', requires=IS_IN_SET(['car', 'bike', 'book', 'music', 'outdoors','household','misc.'])),
   Field('image_file', 'upload'),
   Field('price', requires=IS_NOT_EMPTY()),
   Field('description', 'text', requires=IS_NOT_EMPTY()),
   Field('created_on', 'datetime', default=request.now),
   Field('User_ID', 'reference auth_user', readable=False, writable=False),
   Field('sold', 'boolean', writable=True,readable=True,default=False),
   auth.signature)

db.listing.phone_number.requires = IS_MATCH('^1?((-)\d{3}-?|\(\d{3}\))\d{3}-?\d{4}$', error_message='not a phone number')
db.listing.price.requires = IS_FLOAT_IN_RANGE(0, 100000.0,error_message='The price should be in the range 0..100000')
db.listing.title.requires = IS_NOT_IN_DB(db, db.listing.title)
db.listing.created_on.readable = db.listing.created_on.writable = False

db.define_table('images',
   Field('post_ID',readable=False,writable=False),
   Field('User_ID', 'reference auth_user',readable=False,writable=False),
   Field('image','upload'),
   format = '%(image)s')

db.define_table('voting',
   Field('ratee', 'reference auth_user'),
   Field('updown'),
   Field('rater', 'reference auth_user'))
