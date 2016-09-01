db = DAL("sqlite://storage.sqlite")

db.define_table('sell',
   Field('title', unique=True),
   Field('file', 'upload'),
   Field('description', requires = IS_LENGTH(150)),
   Field('date_posted', 'date', default=request.now, requires = IS_DATE(format=T('%m-%d-%Y'), error_message='must be MM-DD-YYYY!')), 
   Field('category', requires = IS_IN_SET(['Car', 'Bike', 'Book', 'Music', 'Outdoors', 'Household', 'Misc.'])),
   Field('price', 'float', requires = IS_FLOAT_IN_RANGE(0, 100000.0,
       error_message='The price needs to be between $0 and 100000')),
   Field('email', requires = IS_EMAIL()),
   Field('phone_number'),
   Field('listing_status', 'boolean', default=False),
   format = '%(title)s')
      
db.sell.title.requires = IS_NOT_IN_DB(db, db.sell.title)
db.sell.phone_number.requires = IS_MATCH('^1?((-)\d{3}-?|\(\d{3}\))\d{3}-?\d{4}$',
         error_message='Need format *-***-***-****')

from gluon.tools import Auth
auth = Auth(db)
auth.define_tables(username=True)


'''
db.define_table('post',
   Field('image_id', 'reference image'),
   Field('author'),
   Field('email'),
   Field('body', 'text'))

db.post.image_id.requires = IS_IN_DB(db, db.image.id, '%(title)s')
db.post.author.requires = IS_NOT_EMPTY()
db.post.email.requires = IS_EMAIL()
db.post.body.requires = IS_NOT_EMPTY()

db.post.image_id.writable = db.post.image_id.readable = False

'''
