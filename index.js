'use strict'

const benchmark = require('benchmark')
const formatting = require('./build/Release/formatting')

const numeral = require('numeral')
numeral.language('ja', require('numeral/languages/ja'))

const Globalize = require('globalize')
Globalize.load( require( "cldr-data" ).entireSupplemental() );
Globalize.load( require( "cldr-data" ).entireMainFor( "en", "ja" ) );
Globalize.locale('ja')

const numbro = require('numbro')
numbro.language('ja-JP')

const suite = new benchmark.Suite
suite
.add('native', () => {
        formatting.ICUFormatNumber(123.123123)
})
.add('numeraljs', () => {
        numeral(123.123123).format()
})
.add('globalize', () => {
        Globalize.formatNumber(123.123123)
})
.add('numbro', () => {
        numbro(123.123123).format()
})
.add('boost format', () => {
        formatting.BoostFormatNumber(123123.123123)
})
.add('boost locale number', () => {
        formatting.BoostLocaleFormatNumber(123123.123123)
})
.on('cycle', function(event) {
  console.log(String(event.target));
})
.on('complete', function() {
  console.log('Fastest is ' + this.filter('fastest').map('name'));
})
.run()
